package version

// https://belief-driven-design.com/build-time-variables-in-go-51439b26ef9/

import "fmt"

var (
	version        = "dev"
	commitHash     = "n/a"
	buildTimestamp = "n/a"
	LogStderr      = "false"
)

func BuildVersion() string {
	return fmt.Sprintf("%s-%s (%s)", version, commitHash, buildTimestamp)
}
