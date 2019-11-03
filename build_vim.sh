#! /bin/sh
# vim_cv_terminfo = ?? yes or no ?? If yes, will have to set it
# vim_cv_stat_ignores_slash = unknown. Test with yes, rerun with no
# All stuff with tgetent / terminfo will have to be hardcoded
# tty_group too.
# vim_cv_memmove_handles_overlap = set to no for safety
# vim_cv_memcpy_handles_overlap = same

# -g2 for debugging 

# 1) configure 
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no LUA_PREFIX=${PWD}  vi_cv_path_plain_lua=/usr/bin/lua vi_cv_version_plain_lua=5.3.4 --with-tlib=ncurses --with-features=big --enable-terminal --enable-luainterp --enable-python3interp --with-python3-command=python3 CC=clang CXX=clang++ CFLAGS="-DEXITFREE -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/ -fembed-bitcode" CPPFLAGS="-DEXITFREE -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/" CXXFLAGS="-DEXITFREE -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/ -fembed-bitcode" LDFLAGS="-shared -arch arm64 -g2 -miphoneos-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS.sdk/ "  --build=x86_64-apple-darwin --host=armv7-apple-darwin 

# 2) make. This creates ./src/vim, a Mach-O 64-bit dynamically linked shared library for arm64. 
make

# 3) 
echo "Creating: " Frameworks/vim.framework
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


# DONE: add LDFLAGS
# DONE: compile as dylib, not executable
# DONE: add ios_system
# DONE: test inside a-shell
# DONE: forward input
# DONE: remove -g2
# DONE: replace fork with ios_fork, wait for streams.
# DONE: provide missing termcap functions, from hterm POV
# DONE: see termlib.c for help
# TODO: add Python & Lua support (FEAT_PYTHON, FEAT_LUA...)
# DONE: remove /bin/sh from shell commands
