// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterFysh",
    products: [
        .library(name: "TreeSitterFysh", targets: ["TreeSitterFysh"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterFysh",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                // NOTE: if your language has an external scanner, add it here.
                "src/scanner.c",
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterFyshTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterFysh",
            ],
            path: "bindings/swift/TreeSitterFyshTests"
        )
    ],
    cLanguageStandard: .c11
)
