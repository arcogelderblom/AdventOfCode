#!/bin/bash

cd GenericLib
cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release
cmake --build _build --config Release
cmake --install _build
cd ..
