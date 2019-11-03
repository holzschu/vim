#! /bin/sh
# vim_cv_terminfo = ?? yes or no ?? If yes, will have to set it
# vim_cv_stat_ignores_slash = unknown. Test with yes, rerun with no
# All stuff with tgetent / terminfo will have to be hardcoded
# tty_group too.
# vim_cv_memmove_handles_overlap = set to no for safety
# vim_cv_memcpy_handles_overlap = same

# 1) configure 
./configure vim_cv_toupper_broken=no vim_cv_terminfo=no vim_cv_tgetent=zero vim_cv_memmove_handles_overlap=no vim_cv_memcpy_handles_overlap=no vim_cv_bcopy_handles_overlap=no vim_cv_tty_group=world vim_cv_stat_ignores_slash=yes vim_cv_getcwd_broken=no --with-tlib=ncurses --with-features=big --enable-terminal CC=clang CXX=clang++ CFLAGS="-DEXITFREE -g2 -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/ -fembed-bitcode" CPPFLAGS="-DEXITFREE -g2 -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/" CXXFLAGS="-DEXITFREE -g2 -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/ -fembed-bitcode" LDFLAGS="-g2 -shared -mios-simulator-version-min=11.0 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator.sdk/ -fembed-bitcode"  --build=x86_64-apple-darwin --host=armv7-apple-darwin 

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
# DONE: memory issues (again)
# DONE: remove tgetstr, tputs, etc;
# DONE: replace fork with ios_fork, wait for streams.
# DONE: provide missing termcap functions, from hterm POV
# DONE: see termlib.c for help
# TODO: add Python & Lua support (FEAT_PYTHON, FEAT_LUA...)
# DONE: remove /bin/sh from shell commands
# DONE: send resize events to vim, one way or another
# TODO: avoid compose events in command mode. HOW? (sucks for everyone, though)
# TODO: visual bell

# a-shell:
# DONE: remove insert mode in hterm.html, always in overwrite
# TODO: empjis need multiple characters. CJK works here, why not emojis?
# TODO: move javascript out of hterm.html, into myown.js
# Check that toolbar stays on always (?)

