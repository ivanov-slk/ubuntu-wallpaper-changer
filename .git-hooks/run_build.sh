#! /usr/bin/bash
start_time=$(date +%s)
echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Starting build..."
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${DIR}/../build"
echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] in $(pwd)"
# rm -r *

echo "$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Compiling..."
cmake -D CMAKE_C_COMPILER=/usr/bin/gcc-10 -D CMAKE_CXX_COMPILER=/usr/bin/g++-10 ..
make -j 3
echo -e "\n$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Running tests..."
test/run_tests
end_time=$(date +%s)
echo -e "\n$(printf '%(%Y-%m-%d %H:%M:%S)T\n' -1) [BUILD] Build finished for $(($end_time-$start_time)) seconds."
