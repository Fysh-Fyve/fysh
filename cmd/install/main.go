package main

// https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
	"strings"
	"time"
)

const PACKAGE = "github.com/Fysh-Fyve/fyshls"

func X(k, v string) string { return fmt.Sprintf("-X '%s/version.%s=%s'", PACKAGE, k, v) }

func run(args ...string) string {
	cmd := exec.Command(args[0], args[1:]...)
	if output, err := cmd.Output(); err == nil {
		return strings.TrimSpace(string(output))
	}
	return ""
}

func main() {
	outputFile := flag.String("o", "", "Output path of the executable")
	flag.Parse()
	version := run("git", "describe", "--tags", "--always", "--abbrev=0", "--match=v[0-9]*.[0-9]*.[0-9]*")
	commitHash := run("git", "rev-parse", "--short", "HEAD")
	buildTimeStamp := time.Now().Format("2006-01-02T15:04:05")

	// Set linker flags
	ldflags := strings.Join(
		[]string{
			X("version", version),
			X("commitHash", commitHash),
			X("buildTimestamp", buildTimeStamp),
			X("LogStderr", "true"),
		},
		" ",
	)

	args := os.Args[1:]

	var cmd *exec.Cmd
	if *outputFile != "" {
		cmd = exec.Command("go", "build", "-o", *outputFile, "-ldflags", ldflags)
	} else if len(args) == 1 {
		cmd = exec.Command("go", "build", "-o", args[0], "-ldflags", ldflags)
	} else if len(args) == 0 {
		cmd = exec.Command("go", "install", "-ldflags", ldflags)
	} else {
		fmt.Printf("USAGE:\n  %s [PATH]\n  %s -o PATH\n", os.Args[0], os.Args[0])
		os.Exit(1)
	}

	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	if err := cmd.Run(); err != nil {
		fmt.Println("error: ", err)
		os.Exit(1)
	}
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
