#! /usr/bin/bash
start_time=$(date +%s)
echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Starting build..."
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Currently in $DIR."
mkdir -p "${DIR}/../test/resources/dir_tests/test_dir2/empty_dir"
BUILD_DIR="${DIR}/../build"
mkdir -p $BUILD_DIR
cd $BUILD_DIR
echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Switched to $(pwd)."

echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Compiling..."
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-12 -D CMAKE_CXX_COMPILER=/usr/bin/g++-12 ..
make -j 3
echo -e "\n$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Running tests..."
test/run_tests
end_time=$(date +%s)
echo -e "\n$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Build finished for $(($end_time-$start_time)) seconds."
