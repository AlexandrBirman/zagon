#!/bin/bash

# Script to build and run project for development purposes

set -euo pipefail

echo "Build project"
mkdir -p build
cmake -B ./build -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build --target all
echo "Build complete"

echo "Run project"
./build/zagon