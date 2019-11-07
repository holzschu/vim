#!/bin/bash

IOS_SYSTEM_VER="2.4"

HHROOT="https://github.com/holzschu"

mkdir -p "${BASH_SOURCE%/*}/Frameworks"

(cd "${BASH_SOURCE%/*}/Frameworks"
# ios_system
echo "Downloading Frameworks:"
curl -OL $HHROOT/ios_system/releases/download/v$IOS_SYSTEM_VER/release.tar.gz
( tar -xzf release.tar.gz --strip 1 && rm release.tar.gz ) || { echo "ios_system failed to download"; exit 1; }
)

(cd "${BASH_SOURCE%/*}/src/"
# ios_error.h
curl -OL $HHROOT/ios_system/releases/download/v$IOS_SYSTEM_VER/ios_error.h
)

