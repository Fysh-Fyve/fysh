#!/bin/bash

# https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/

PACKAGE="github.com/Fysh-Fyve/fyshls"
VERSION="$(git describe --tags --always --abbrev=0 --match='v[0-9]*.[0-9]*.[0-9]*' 2> /dev/null | sed 's/^.//')"
COMMIT_HASH="$(git rev-parse --short HEAD)"
BUILD_TIMESTAMP=$(date '+%Y-%m-%dT%H:%M:%S')

LDFLAGS=(
  "-X '${PACKAGE}/version.version=${VERSION}'"
  "-X '${PACKAGE}/version.commitHash=${COMMIT_HASH}'"
  "-X '${PACKAGE}/version.buildTimestamp=${BUILD_TIMESTAMP}'"
)

go build -o $1 -ldflags="${LDFLAGS[*]}"
