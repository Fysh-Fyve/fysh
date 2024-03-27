package main

// https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/

import (
	"fmt"
	"os"
	"os/exec"
	"strings"
	"time"
)

var (
	PACKAGE         = "github.com/Fysh-Fyve/fyshls"
	VERSION         string
	COMMIT_HASH     string
	BUILD_TIMESTAMP string
)

func main() {
	// Retrieve version, commit hash, and build timestamp
	getVersionInfo()

	// Set linker flags
	ldflags := fmt.Sprintf("-X '%s/version.version=%s' -X '%s/version.commitHash=%s' -X '%s/version.buildTimestamp=%s' -X '%s/version.LogStderr=true'",
		PACKAGE, VERSION,
		PACKAGE, COMMIT_HASH,
		PACKAGE, BUILD_TIMESTAMP,
		PACKAGE)

	args := os.Args[1:]

	if len(args) > 0 {
		// Build binary with provided name
		if err := buildBinary(args[0], ldflags); err != nil {
			fmt.Println("Error:", err)
			os.Exit(1)
		}
	} else {
		// Install package with linker flags
		if err := installPackage(ldflags); err != nil {
			fmt.Println("Error:", err)
			os.Exit(1)
		}
	}
}

func getVersionInfo() {
	// Retrieve version from git describe
	versionCmd := exec.Command("git", "describe", "--tags", "--always", "--abbrev=0", "--match=v[0-9]*.[0-9]*.[0-9]*")
	if output, err := versionCmd.Output(); err == nil {
		VERSION = strings.TrimSpace(string(output)[1:]) // Remove leading 'v'
	}

	// Retrieve commit hash
	commitHashCmd := exec.Command("git", "rev-parse", "--short", "HEAD")
	if output, err := commitHashCmd.Output(); err == nil {
		COMMIT_HASH = strings.TrimSpace(string(output))
	}

	// Set build timestamp
	BUILD_TIMESTAMP = time.Now().Format("2006-01-02T15:04:05")
}

func buildBinary(outputFile, ldflags string) error {
	cmd := exec.Command("go", "build", "-o", outputFile, "-ldflags", ldflags)
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	return cmd.Run()
}

func installPackage(ldflags string) error {
	cmd := exec.Command("go", "install", "-ldflags", ldflags, ".")
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	return cmd.Run()
}

// Jippitied from this script
// #!/bin/bash
//
// # https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/
//
// PACKAGE="github.com/Fysh-Fyve/fyshls"
// VERSION="$(git describe --tags --always --abbrev=0 --match='v[0-9]*.[0-9]*.[0-9]*' 2> /dev/null | sed 's/^.//')"
// COMMIT_HASH="$(git rev-parse --short HEAD)"
// BUILD_TIMESTAMP=$(date '+%Y-%m-%dT%H:%M:%S')
//
// LDFLAGS=(
//   "-X '${PACKAGE}/version.version=${VERSION}'"
//   "-X '${PACKAGE}/version.commitHash=${COMMIT_HASH}'"
//   "-X '${PACKAGE}/version.buildTimestamp=${BUILD_TIMESTAMP}'"
//   "-X '${PACKAGE}/version.LogStderr=true'"
// )
//
// if [[ "$#" -gt 0 ]]
// then
//   go build -o $1
// else
//   go install -ldflags="${LDFLAGS[*]}" .
// fi
