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
            checksum: "0a1d915355b7f7301cfabffb8bb543355ace8377a174d73065f488816d464c93"
        ),
        .binaryTarget(
            name: "xxd",
            url: "https://github.com/holzschu/vim/releases/download/ios_1.0/xxd.xcframework.zip",
            checksum: "e4497125969914be5dd7fc8012b71646dbc7a5b3f50f50d8254682a8a369dd5b"
        )
    ]
)

