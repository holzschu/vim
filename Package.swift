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
            checksum: "b60b9bfd71091fb008a3aeeb164d9de1d131e5709ec0ae30b933b592aab86dbd"
        )
    ]
)
