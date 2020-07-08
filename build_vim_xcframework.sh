#! /bin/sh

# vim is in an "in-between" state: it depends on Python and TeX frameworks, which have not yet moved to XCframeworks. For the time being, we assume the frameworks are already in the right place. Later, we'll put in place automatic downloading.

# configure and make assume all Frameworks are in ./Frameworks so we move things in place:

echo "Building for iOS:"
rm Frameworks
ln -s Frameworks_iOS Frameworks

make distclean
# 1) configure 
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no LUA_PREFIX=${PWD}  vi_cv_path_plain_lua=/usr/bin/lua vi_cv_version_plain_lua=5.3.4 --with-tlib=ncurses --with-features=big --enable-terminal --enable-luainterp --enable-python3interp --with-python3-command=python3 CC=clang CXX=clang++ CFLAGS="-DEXITFREE -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/ -fembed-bitcode" CPPFLAGS="-DEXITFREE -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/" CXXFLAGS="-DEXITFREE -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/ -fembed-bitcode" LDFLAGS="-shared -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/ "  --build=x86_64-apple-darwin --host=armv7-apple-darwin 

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

echo "Building for Simulator:"
rm Frameworks
ln -s Frameworks_Simulator Frameworks

make distclean
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no --with-tlib=ncurses --with-features=big --enable-terminal CC=clang CXX=clang++ CFLAGS="-DEXITFREE -g2 -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/ -fembed-bitcode" CPPFLAGS="-DEXITFREE -g2 -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/" CXXFLAGS="-DEXITFREE -g2 -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/ -fembed-bitcode" LDFLAGS="-g2 -shared -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode-beta.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/ -fembed-bitcode"  --build=x86_64-apple-darwin --host=armv7-apple-darwin 

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

# 6)
echo "Merging into xcframeworks:"
rm Frameworks

for framework in vim
do
   rm -rf $framework.xcframework
   xcodebuild -create-xcframework -framework Frameworks_iOS/$framework.framework -framework Frameworks_Simulator/$framework.framework -output $framework.xcframework
   # while we're at it, let's compute the checksum:
   rm -f $framework.xcframework.zip
   zip -r $framework.xcframework.zip $framework.xcframework
   swift package compute-checksum $framework.xcframework.zip
done


