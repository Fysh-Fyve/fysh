// Deploy script for github pages
// Loosely based on Docusaurus Github Pages deploy script
// https://github.com/facebook/docusaurus/blob/542228ee1beb5cfddd7ba8ae088f109f164e80c5/packages/docusaurus/src/commands/deploy.ts#L43

package main

import (
	"fmt"
	"log"
	"os"
	"path"
	"path/filepath"
	"strings"

	"github.com/bitfield/script"
	"github.com/plus3it/gorecurcopy"
)

var buildDir = path.Join("dist", "pkg", "website")

const (
	originUrl        = "https://github.com/Fysh-Fyve/Fysh-Fyve.github.io"
	projectName      = "fysh-fyve.github.io"
	deploymentBranch = "gh-pages"
	buildCmd         = ""
)

func execCmd(cmd string) error {
	if cmd == "" {
		return nil
	}
	log.Println(cmd)
	p := script.Exec(cmd)
	p.Stdout()
	return p.Error()
}

func getCmdOutput(cmd string) string {
	out, err := script.Exec(cmd).String()
	if err != nil {
		log.Fatalf("failed command `%s`: %v", cmd, err)
	}
	return strings.TrimSpace(out)
}

func mkTmpDir() (string, func()) {
	dir, err := os.MkdirTemp(os.TempDir(), projectName+"-"+deploymentBranch)
	if err != nil {
		log.Fatalf("failed to make temp dir: %v", err)
	}
	return dir, func() {
		if err := os.RemoveAll(dir); err != nil {
			log.Printf("failed to remove dir: %v\n", err)
		}
	}
}

func dieIf(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	if err := os.RemoveAll("public"); err != nil {
		log.Printf("failed to remove dir: %v\n", err)
	}
	getCmdOutput("git config --get remote.origin.url")
	latestHash := getCmdOutput("git rev-parse HEAD")

	dieIf(execCmd(buildCmd))

	src, err := filepath.Abs(buildDir)
	dieIf(err)
	gitPublish, cleanGitPublish := mkTmpDir()
	defer cleanGitPublish()

	os.Chdir(gitPublish)
	cloneCmd := fmt.Sprintf("git clone --depth 1 --branch \"%s\" \"%s\" \"%s\"", deploymentBranch, originUrl, gitPublish)
	if err := execCmd(cloneCmd); err != nil {
		// Branch doesn't exist, create new branch
		dieIf(execCmd("git init"))
		dieIf(execCmd("git checkout -b " + deploymentBranch))
		dieIf(execCmd("git remote add origin " + originUrl))
	} else {
		dieIf(execCmd("git rm -rf .")) // Simply remove all files
	}
	if err := gorecurcopy.CopyDirectory(src, gitPublish); err != nil {
		log.Fatalf("failed to copy output to publish dir: %v", err)
	}
	os.Chdir(gitPublish)
	dieIf(execCmd("git add --all"))
	commitErr := execCmd(fmt.Sprintf("git commit -m \"Deploy website - based on %s\"", latestHash))
	if err := execCmd("git push --force origin " + deploymentBranch); err != nil {
		log.Fatalf("failed to push to origin: %v", err)
	} else if commitErr == nil {
		fmt.Printf("Website is live at: https://%s\n", projectName)
	}
}
