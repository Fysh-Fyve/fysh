package util

import (
	"fmt"
	"strings"
	"time"

	"github.com/bitfield/script"
)

const PACKAGE = "github.com/Fysh-Fyve/fyshls"

func X(k, v string) string { return fmt.Sprintf("-X '%s/version.%s=%s'", PACKAGE, k, v) }

func GetLDFlags(extra ...string) (string, string, error) {
	version, err := script.Exec("git describe --tags --always --abbrev=0 --match=v[0-9]*.[0-9]*.[0-9]*").String()
	if err != nil {
		return "", "", err
	}
	version = strings.TrimSpace(version)
	commitHash, err := script.Exec("git rev-parse --short HEAD").String()
	if err != nil {
		return "", "", err
	}
	commitHash = strings.TrimSpace(commitHash)
	buildTimeStamp := time.Now().Format("2006-01-02T15:04:05")

	// Set linker flags
	ldflags := []string{
		X("version", version),
		X("commitHash", commitHash),
		X("buildTimestamp", buildTimeStamp),
		X("LogStderr", "true"),
	}
	ldflags = append(ldflags, extra...)
	return strings.Join(ldflags, " "), version, nil
}
