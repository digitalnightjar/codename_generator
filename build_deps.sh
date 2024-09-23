#!/bin/bash
# Extract, Make and Install the cpp-httplib library
cd libs
tar -xzvf ./cpp-httplib-0.13.3.tar.gz
cd ./cpp-httplib-0.13.3
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target install
