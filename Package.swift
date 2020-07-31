// swift-tools-version:5.3

import PackageDescription

let package = Package(
    name: "vim",
    products: [
        .library(name: "vim", targets: ["vim"])
    ],
    dependencies: [
    ],
    targets: [
        .binaryTarget(
            name: "vim",
            url: "https://github.com/holzschu/vim/releases/download/ios_1.0/vim.xcframework.zip",
            checksum: "eb3d7aec0526456f2a9959f5b63ccbc8821dba54a9320d12f93a81c929c1885b"
        )
    ]
)
