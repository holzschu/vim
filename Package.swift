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
            checksum: "be178d89820a7541b1a85d7eee6a3b7f730af24a25a8ff343355dfc2d461d782"
        )
    ]
)
