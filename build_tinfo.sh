#!/bin/sh
set -eu

# ncurses configure splits its auxiliary-file search paths at whitespace.
case $PWD in
    *[[:space:]]*)
        printf '%s\n' 'Build Vim from a checkout path without whitespace.' >&2
        exit 2 ;;
esac

sdk=$1
shift
case $sdk in
    iphoneos) platform=ios ;;
    iphonesimulator) platform=ios-simulator ;;
    *) exit 2 ;;
esac

build=$PWD/.build/tinfo
archive=$build/ncurses-6.6.tar.gz
source=$build/ncurses-6.6
mkdir -p "$build/$sdk/lib"
if [ ! -f "$archive" ]; then
    curl --fail --location --retry 3 https://ftp.gnu.org/gnu/ncurses/ncurses-6.6.tar.gz -o "$archive.tmp"
    mv "$archive.tmp" "$archive"
fi
printf '%s  %s\n' 355b4cbbed880b0381a04c46617b7656e362585d52e9cf84a67e2009b749ff11 "$archive" | shasum -a 256 -c -
tar -xzf "$archive" -C "$build"
build_host=$(sh "$source/config.guess")
build_cc="$(xcrun --sdk macosx -f clang) -isysroot $(xcrun --sdk macosx --show-sdk-path)"
cc=$(xcrun --sdk "$sdk" -f clang)
sdkroot=$(xcrun --sdk "$sdk" --show-sdk-path)

namespace=$PWD/src/ios_tinfo.h
for arch do
    case $platform in
        ios) target=$arch-apple-ios14.0 ;;
        ios-simulator) target=$arch-apple-ios14.0-simulator ;;
    esac
    flags="-target $target -isysroot $sdkroot"
    slice=$build/$sdk/$arch
    mkdir -p "$slice"
    (
        trap 'tail -40 "$slice/build.log" >&3' EXIT
        cd "$slice"
        # a-Shell supplies its bundled hex-directory database through TERMINFO.
        "$source/configure" --build="$build_host" --host="$arch-apple-darwin" \
            --with-build-cc="$build_cc" --with-termlib --with-ospeed=speed_t --prefix=/usr \
            --enable-database --disable-mixed-case --disable-widec \
            --without-shared --without-debug --without-ada --without-cxx --without-cxx-binding \
            --without-manpages --without-progs --without-tests --disable-db-install \
            CC="$cc" CFLAGS="$flags -O2 -fPIC -include $namespace" CPPFLAGS="$flags" LDFLAGS="$flags" LIBS=
        make -C include
        # Fatal errors must exit the ios_system command, not the app.
        make -j4 -C ncurses "CFLAGS_NORMAL=\$(CCFLAGS) -DNCURSES_STATIC -Dexit=ios_exit" ../lib/libtinfo.a
        trap - EXIT
    ) 3>&2 > "$slice/build.log" 2>&1
done

ln -sfn "$build/$sdk/$1/include" "$build/$sdk/ncurses"
for arch do
    set -- "$@" "$build/$sdk/$arch/lib/libtinfo.a"
    shift
done
lipo -create "$@" -output "$build/$sdk/lib/libtinfo.a"
