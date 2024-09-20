package main

// https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/

import (
	"flag"
	"fmt"
	"log"
	"os"
	"os/exec"

	"github.com/Fysh-Fyve/fysh/pkg/fyshls/cmd/util"
)

const PACKAGE = "github.com/Fysh-Fyve/fysh/pkg/fyshls"

func main() {
	outputFile := flag.String("o", "", "Output path of the executable")
	flag.Parse()
	ldflags, _, err := util.GetLDFlags()
	if err != nil {
		log.Fatal(err)
	}

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
		log.Fatal(err)
	}
}

// Jippitied from this script
// #!/bin/bash
//
// # https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/
//
// PACKAGE="github.com/Fysh-Fyve/fysh/pkg/fyshls"
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
