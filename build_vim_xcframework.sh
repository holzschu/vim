#!/bin/bash
set -euo pipefail

# The Python bridge loads the application framework dynamically; only headers are needed here.
mkdir -p .build/deps
curl --fail --location --retry 3 https://github.com/holzschu/ios_system/releases/download/v3.0.5/ios_system.xcframework.zip -o .build/deps/ios_system.xcframework.zip
curl --fail --location --retry 3 https://github.com/holzschu/lua_ios/releases/download/1.0/lua_ios.xcframework.zip -o .build/deps/lua_ios.xcframework.zip
curl --fail --location --retry 3 https://www.lua.org/ftp/lua-5.3.4.tar.gz -o .build/deps/lua-5.3.4.tar.gz
curl --fail --location --retry 3 https://github.com/holzschu/a-shell/releases/download/cpython_05_22/pythonInstall.tar.gz -o .build/deps/pythonInstall.tar.gz
shasum -a 256 -c - <<'CHECKSUMS'
d429e68102926f58bedd8e8b7105dcd169478cd6da1cef494a5f468482d1c8f5  .build/deps/ios_system.xcframework.zip
0ccdab671f31c20daf8833452cc36598b49f84441851d7142b305443425bc527  .build/deps/lua_ios.xcframework.zip
f681aa518233bc407e23acf0f5887c884f17436f000d453b2491a9f11a52400c  .build/deps/lua-5.3.4.tar.gz
603d621a7bb5bc196fbd9309448d8231246d83371196285483430eea7c3b1f65  .build/deps/pythonInstall.tar.gz
CHECKSUMS
unzip -oq .build/deps/ios_system.xcframework.zip -d .build/deps
unzip -oq .build/deps/lua_ios.xcframework.zip -d .build/deps
tar -xzf .build/deps/lua-5.3.4.tar.gz -C .build/deps
mkdir -p .build/deps/lua-5.3.4/include
cp .build/deps/lua-5.3.4/src/*.h .build/deps/lua-5.3.4/include/
tar -xzf .build/deps/pythonInstall.tar.gz -C .build/deps cpython/Library/include cpython/Library/lib/python3.9/config-3.9-darwin
PYTHON_PREFIX="$PWD/.build/deps/cpython/Library"
BUILD_TRIPLE="$(uname -m)-apple-darwin$(uname -r)"
for framework in ios_system lua_ios; do
    mkdir -p Frameworks_iOS Frameworks_Simulator
    rm -rf "Frameworks_iOS/$framework.framework" "Frameworks_Simulator/$framework.framework"
    cp -R ".build/deps/$framework.xcframework/ios-arm64/$framework.framework" Frameworks_iOS/
    cp -R ".build/deps/$framework.xcframework/ios-arm64_x86_64-simulator/$framework.framework" Frameworks_Simulator/
done

# configure and make assume all Frameworks are in ./Frameworks so we move things in place:
IOS_SDKROOT=$(xcrun --sdk iphoneos --show-sdk-path)
SIM_SDKROOT=$(xcrun --sdk iphonesimulator --show-sdk-path)

FRAMEWORKS=$PWD/Frameworks 
echo "Building for iOS:"
rm -f Frameworks
ln -s Frameworks_iOS Frameworks

if [ -f src/auto/config.mk ]; then make distclean; fi
# 1) configure 
# --enable-terminal 
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no LUA_PREFIX="$PWD/.build/deps/lua-5.3.4"  vi_cv_path_plain_lua=/usr/bin/lua vi_cv_version_plain_lua=5.3 --with-tlib=ncurses --with-features=big --enable-luainterp --enable-python3interp=dynamic --with-python3-command=python3 vi_cv_var_python3_version=3.9 vi_cv_var_python3_abiflags= vi_cv_path_python3_pfx="$PYTHON_PREFIX" vi_cv_path_python3_epfx="$PYTHON_PREFIX" vi_cv_path_python3_conf="$PYTHON_PREFIX/lib/python3.9/config-3.9-darwin" vi_cv_path_python3_plibs=" " vi_cv_dll_name_python3=python3 CC=clang CXX=clang++ CFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -DDYNAMIC_PYTHON3" CPPFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -DDYNAMIC_PYTHON3" CXXFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -DDYNAMIC_PYTHON3" LDFLAGS="-shared -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -F$FRAMEWORKS -framework ios_system "  --build="$BUILD_TRIPLE" --host=arm-apple-darwin

grep -q '^#define FEAT_PYTHON3 1' src/auto/config.h
grep -q '^#define FEAT_LUA 1' src/auto/config.h

# 2) make. This creates ./src/vim, a Mach-O 64-bit dynamically linked shared library for arm64. 
make -j3

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
rm -f Frameworks
ln -s Frameworks_Simulator Frameworks

make distclean
#  --enable-terminal
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no --with-tlib=ncurses --with-features=big CC=clang CPP="clang -E" CXX=clang++ CFLAGS="-DEXITFREE -arch arm64 -arch x86_64 -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT" CPPFLAGS="-DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT" CXXFLAGS="-DEXITFREE -arch arm64 -arch x86_64 -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT" LDFLAGS="-arch arm64 -arch x86_64 -O2 -shared -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT  -F$FRAMEWORKS -framework ios_system "  --build="$BUILD_TRIPLE" --host=arm-apple-darwin

# 2) make. This creates ./src/vim, a Mach-O 64-bit dynamically linked shared library for arm64. 
make -j3

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
rm -f Frameworks

for framework in vim xxd
do
   rm -rf $framework.xcframework
   xcodebuild -create-xcframework -framework Frameworks_iOS/$framework.framework -framework Frameworks_Simulator/$framework.framework -output $framework.xcframework
   # while we're at it, let's compute the checksum:
   rm -f $framework.xcframework.zip
   zip -rq $framework.xcframework.zip $framework.xcframework
   swift package compute-checksum $framework.xcframework.zip
done


