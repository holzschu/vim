#! /bin/sh

# vim is in an "in-between" state: it depends on Python and TeX frameworks, which have not yet moved to XCframeworks. For the time being, we assume the frameworks are already in the right place. Later, we'll put in place automatic downloading.

# configure and make assume all Frameworks are in ./Frameworks so we move things in place:
OSX_SDKROOT=$(xcrun --sdk macosx --show-sdk-path)
IOS_SDKROOT=$(xcrun --sdk iphoneos --show-sdk-path)
SIM_SDKROOT=$(xcrun --sdk iphonesimulator --show-sdk-path)

use_tinfo() {
    tinfo=$PWD/.build/tinfo/$1
    # The termcap.h configure probe needs Darwin's speed_t from termios.h.
    tinfo_cppflags="-include termios.h -I$tinfo -I$tinfo/ncurses -DHAVE_TGETENT -DVIM_PRIVATE_TINFO -include $PWD/src/ios_tinfo.h"
    tinfo_ldflags="-L$tinfo/lib -Xlinker -load_hidden -Xlinker $tinfo/lib/libtinfo.a -Wl,-dead_strip"
}

FRAMEWORKS=$PWD/Frameworks
echo "Building for iOS:"
rm Frameworks
ln -s Frameworks_iOS Frameworks

make distclean
# 1) configure 
# --enable-terminal 
sh build_tinfo.sh iphoneos arm64 || exit 1
use_tinfo iphoneos
./configure vim_cv_toupper_broken=no vim_cv_terminfo=yes vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no LUA_PREFIX=${PWD}  vi_cv_path_plain_lua=/usr/bin/lua vi_cv_version_plain_lua=5.4.4 --with-tlib=tinfo --with-features=big --enable-luainterp --enable-python3interp --with-python3-command=python3 CC=clang CXX=clang++ CFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -fembed-bitcode -DDYNAMIC_PYTHON3" CPPFLAGS="$tinfo_cppflags -DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -DDYNAMIC_PYTHON3" CXXFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -fembed-bitcode -DDYNAMIC_PYTHON3" LDFLAGS="$tinfo_ldflags -shared -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -F$FRAMEWORKS -framework ios_system "  --build=x86_64-apple-darwin --host=armv7-apple-darwin  || exit 1

# 2) make. This creates ./src/vim, a Mach-O 64-bit dynamically linked shared library for arm64. 
make

# 3) 
echo "Creating: Frameworks/vim.framework"
framework=vim
libraryFile=src/vim
rm -rf Frameworks/$framework.framework
mkdir -p Frameworks/$framework.framework
cp $libraryFile Frameworks/$framework.framework/$framework
cp basic_Info.plist Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleExecutable -string $framework Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleName -string $framework Frameworks/$framework.framework/Info.plist
# underscore is not allowed in CFBundleIdentifier:
signature=${framework//_/-}
plutil -replace CFBundleIdentifier -string Nicolas-Holzschuch.$signature  Frameworks/$framework.framework/Info.plist
install_name_tool -id @rpath/$framework.framework/$framework  Frameworks/$framework.framework/$framework

echo "Creating: Frameworks/xxd.framework"
framework=xxd
libraryFile=src/xxd/xxd
rm -rf Frameworks/$framework.framework
mkdir -p Frameworks/$framework.framework
cp $libraryFile Frameworks/$framework.framework/$framework
cp basic_Info.plist Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleExecutable -string $framework Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleName -string $framework Frameworks/$framework.framework/Info.plist
# underscore is not allowed in CFBundleIdentifier:
signature=${framework//_/-}
plutil -replace CFBundleIdentifier -string Nicolas-Holzschuch.$signature  Frameworks/$framework.framework/Info.plist
install_name_tool -id @rpath/$framework.framework/$framework  Frameworks/$framework.framework/$framework



echo "Building for Simulator:"
rm Frameworks
ln -s Frameworks_Simulator Frameworks

make distclean
#  --enable-terminal
sh build_tinfo.sh iphonesimulator "$(uname -m)" || exit 1
use_tinfo iphonesimulator
./configure vim_cv_toupper_broken=no vim_cv_terminfo=yes vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no --with-tlib=tinfo --with-features=big CC=clang CXX=clang++ CFLAGS="-DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT -fembed-bitcode" CPPFLAGS="$tinfo_cppflags -DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT" CXXFLAGS="-DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT -fembed-bitcode" LDFLAGS="$tinfo_ldflags -O2 -shared -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT -fembed-bitcode  -F$FRAMEWORKS -framework ios_system "  --build=x86_64-apple-darwin --host=armv7-apple-darwin  || exit 1

# 2) make. This creates ./src/vim, a Mach-O 64-bit dynamically linked shared library for arm64. 
make

# 3) 
echo "Creating: Frameworks/vim.framework"
framework=vim
libraryFile=src/vim
rm -rf Frameworks/$framework.framework
mkdir -p Frameworks/$framework.framework
cp $libraryFile Frameworks/$framework.framework/$framework
cp basic_Info_Simulator.plist Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleExecutable -string $framework Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleName -string $framework Frameworks/$framework.framework/Info.plist
# underscore is not allowed in CFBundleIdentifier:
signature=${framework//_/-}
plutil -replace CFBundleIdentifier -string Nicolas-Holzschuch.$signature  Frameworks/$framework.framework/Info.plist
install_name_tool -id @rpath/$framework.framework/$framework  Frameworks/$framework.framework/$framework

echo "Creating: Frameworks/xxd.framework"
framework=xxd
libraryFile=src/xxd/xxd
rm -rf Frameworks/$framework.framework
mkdir -p Frameworks/$framework.framework
cp $libraryFile Frameworks/$framework.framework/$framework
cp basic_Info_Simulator.plist Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleExecutable -string $framework Frameworks/$framework.framework/Info.plist
plutil -replace CFBundleName -string $framework Frameworks/$framework.framework/Info.plist
# underscore is not allowed in CFBundleIdentifier:
signature=${framework//_/-}
plutil -replace CFBundleIdentifier -string Nicolas-Holzschuch.$signature  Frameworks/$framework.framework/Info.plist
install_name_tool -id @rpath/$framework.framework/$framework  Frameworks/$framework.framework/$framework

# 6)
echo "Merging into xcframeworks:"
rm Frameworks

for framework in vim xxd
do
   if [ "$framework" = vim ]; then
       for directory in Frameworks_iOS Frameworks_Simulator; do
           mkdir -p "$directory/vim.framework/Notices" || exit 1
           cp .build/tinfo/ncurses-6.6/COPYING "$directory/vim.framework/Notices/ncurses-COPYING" || exit 1
       done
   fi
   rm -rf $framework.xcframework
   xcodebuild -create-xcframework -framework Frameworks_iOS/$framework.framework -framework Frameworks_Simulator/$framework.framework -output $framework.xcframework
   # while we're at it, let's compute the checksum:
   rm -f $framework.xcframework.zip
   zip -rq $framework.xcframework.zip $framework.xcframework
   swift package compute-checksum $framework.xcframework.zip
done


