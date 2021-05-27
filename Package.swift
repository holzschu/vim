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
            checksum: "b490cce70155afa85cb7477f248b625f3da3359a47d29aa67d5ada849588f9df"
        ),
        .binaryTarget(
            name: "xxd",
            url: "https://github.com/holzschu/vim/releases/download/ios_1.0/xxd.xcframework.zip",
            checksum: "51564908abd1e19678d24e424ed32bb4e39dd8e177e5d27a8b851402ea15937b"
        )
    ]
)
