#! /usr/bin/bash
echo "BUILD: Starting build..."
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${DIR}/../build"
echo "BUILD: in "$(pwd)
# rm -r *
cmake ..
make
test/run_tests