#!/usr/bin/env zsh
set -e

git clone --depth 1 https://dawn.googlesource.com/dawn
cd dawn
git rev-parse HEAD >../dawn.ref
cd ..

rm -rf src
rm -rf include
mkdir -p src/tint
mkdir -p src/utils
mkdir -p include

cp dawn/src/utils/*.h src/utils/
cp -r dawn/src/tint/api src/tint
cp -r dawn/src/tint/lang src/tint
cp -r dawn/src/tint/utils src/tint
cp -r dawn/include/tint include

rm -rf src/**/BUILD.*
rm -rf src/**/*_test.cc
rm -rf src/**/*_bench.cc
rm -rf src/**/*_fuzz.cc

# remove some files to reduce dependencies (we only need SPIRV reading and WGSL writing)
rm -rf src/tint/lang/core/ir/binary

# not needed
rm -rf src/tint/lang/glsl
rm -rf src/tint/lang/hlsl
rm -rf src/tint/lang/msl
rm -rf src/tint/lang/null
rm -rf src/tint/lang/spirv/writer

# language server depends on an external dependencies
rm -rf src/tint/lang/wgsl/ls

# this contains platform specific code, only needed for cmdline tool
rm -rf src/tint/utils/command

# depends on abseil, only used by wgsl reader
rm src/tint/utils/strconv/parse_num.*
rm -rf src/tint/lang/wgsl/reader

# platform specific code
rm src/tint/utils/system/executable*
rm src/tint/utils/system/env_windows.cc
rm src/tint/utils/system/terminal_posix.cc
rm src/tint/utils/system/terminal_windows.cc
rm src/tint/utils/text/*_ansi.cc
rm src/tint/utils/text/*_posix.cc
rm src/tint/utils/text/*_windows.cc

rm -rf src/tint/utils/file
rm -rf src/tint/utils/protos
