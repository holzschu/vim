#! /bin/sh

# vim is in an "in-between" state: it depends on Python and TeX frameworks, which have not yet moved to XCframeworks. For the time being, we assume the frameworks are already in the right place. Later, we'll put in place automatic downloading.

# configure and make assume all Frameworks are in ./Frameworks so we move things in place:
OSX_SDKROOT=$(xcrun --sdk macosx --show-sdk-path)
IOS_SDKROOT=$(xcrun --sdk iphoneos --show-sdk-path)
SIM_SDKROOT=$(xcrun --sdk iphonesimulator --show-sdk-path)

FRAMEWORKS=$PWD/Frameworks 
echo "Building for iOS:"
rm Frameworks
ln -s Frameworks_iOS Frameworks

make distclean
# 1) configure 
# --enable-terminal 
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no LUA_PREFIX=${PWD}  vi_cv_path_plain_lua=/usr/bin/lua vi_cv_version_plain_lua=5.3.4 --with-tlib=ncurses --with-features=big --enable-luainterp --enable-python3interp --with-python3-command=python3 CC=clang CXX=clang++ CFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -fembed-bitcode -DDYNAMIC_PYTHON3" CPPFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -DDYNAMIC_PYTHON3" CXXFLAGS="-DEXITFREE -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -fembed-bitcode -DDYNAMIC_PYTHON3" LDFLAGS="-shared -arch arm64 -O2 -miphoneos-version-min=14.0 -isysroot $IOS_SDKROOT -F$FRAMEWORKS -framework ios_system "  --build=x86_64-apple-darwin --host=armv7-apple-darwin 

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
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no --with-tlib=ncurses --with-features=big CC=clang CXX=clang++ CFLAGS="-DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT -fembed-bitcode" CPPFLAGS="-DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT" CXXFLAGS="-DEXITFREE -O2 -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT -fembed-bitcode" LDFLAGS="-O2 -shared -mios-simulator-version-min=14.0 -isysroot $SIM_SDKROOT -fembed-bitcode  -F$FRAMEWORKS -framework ios_system "  --build=x86_64-apple-darwin --host=armv7-apple-darwin 

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
   rm -rf $framework.xcframework
   xcodebuild -create-xcframework -framework Frameworks_iOS/$framework.framework -framework Frameworks_Simulator/$framework.framework -output $framework.xcframework
   # while we're at it, let's compute the checksum:
   rm -f $framework.xcframework.zip
   zip -rq $framework.xcframework.zip $framework.xcframework
   swift package compute-checksum $framework.xcframework.zip
done


