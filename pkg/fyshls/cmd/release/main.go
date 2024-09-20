package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"path"

	"github.com/Fysh-Fyve/fysh/pkg/fyshls/cmd/util"
	"github.com/bitfield/script"
)

const (
	linuxGCC     = "x86_64-linux-musl-gcc"
	linuxBrewPkg = "FiloSottile/musl-cross/musl-cross"
	winGCC       = "x86_64-w64-mingw32-gcc"
	winBrewPkg   = "mingw-w64"
)

func main() {
	if err := createReleasePackages(); err != nil {
		log.Fatal(err)
	}
	log.Println("successfully uploaded artifacts")
}

var builds = [...][4]string{
	{linuxGCC, "amd64", "linux", "-extldflags=-static"},
	{winGCC, "amd64", "windows"},
	{"", "amd64", "darwin"},
	{"", "arm64", "darwin"},
}

func cleanupFile(name string, err *error) {
	if rerr := os.Remove(name); *err == nil {
		*err = rerr
	}
}

func buildExe(conf [4]string) (err error) {
	ldflags, version, err := util.GetLDFlags(conf[3])
	if err != nil {
		return err
	}
	isWin := conf[2] == "windows"
	exeName := "fyshls"
	if isWin {
		exeName += ".exe"
	}
	cc := ""
	if conf[0] != "" {
		cc = "CC=" + conf[0]
	}
	cmd := exec.Command("go", "build", "-o", exeName, "-ldflags", ldflags)
	cmd.Env = append(cmd.Environ(), "CGO_ENABLED=1", cc, "GOARCH="+conf[1], "GOOS="+conf[2])
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	if err = cmd.Run(); err != nil {
		return err
	}
	// Clean up executable file
	defer cleanupFile(exeName, &err)

	archiveName := path.Join("artifacts", fmt.Sprintf("fyshls-%s-%s-%s", version, conf[2], conf[1]))
	if isWin {
		archiveName += ".zip"
		_, err = script.Exec(fmt.Sprintf("tar czf %s %s LICENSE", archiveName, exeName)).Stdout()
	} else {
		archiveName += ".tar.gz"
		_, err = script.Exec(fmt.Sprintf("zip %s %s LICENSE", archiveName, exeName)).Stdout()
	}
	if err != nil {
		return err
	}

	// Clean up archive file
	defer cleanupFile(archiveName, &err)

	hash := md5.New()
	f, err := os.Open(archiveName)
	if err != nil {
		return err
	}
	_, err = io.Copy(hash, f)
	if err != nil {
		return err
	}
	md5Hash := hash.Sum(nil)
	_, err = script.Echo(hex.EncodeToString(md5Hash) + "\n").WriteFile(archiveName + ".md5")
	if err != nil {
		return err
	}
	defer cleanupFile(archiveName+".md5", &err)

	_, err = script.Exec(fmt.Sprintf("gh release upload --clobber %s %s", version, archiveName)).Stdout()
	if err != nil {
		return err
	}
	_, err = script.Exec(fmt.Sprintf("gh release upload --clobber %s %s", version, archiveName+".md5")).Stdout()
	if err != nil {
		return err
	}

	return nil
}

func createReleasePackages() error {
	if err := installTools(); err != nil {
		return err
	}
	for _, conf := range builds {
		err := buildExe(conf)
		if err != nil {
			return err
		}
	}

	return nil
}

func installTools() error {
	if _, err := installIfNotExists("gh", "gh"); err != nil {
		return err
	}
	if _, err := installIfNotExists(linuxGCC, linuxBrewPkg); err != nil {
		return err
	}
	if _, err := installIfNotExists(winGCC, winBrewPkg); err != nil {
		return err
	}
	return nil
}

func installIfNotExists(exe, pkg string) (string, error) {
	exePath, err := exec.LookPath(exe)
	if err != nil {
		_, err := script.Exec(fmt.Sprintf("brew install %s", pkg)).Stdout()
		if err != nil {
			return "", err
		}
		// Try again :)
		exePath, err = exec.LookPath(exe)
		if err != nil {
			return "", err
		}
	}
	return exePath, err

}
