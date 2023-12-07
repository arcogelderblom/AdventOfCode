#!/bin/bash

cd $1
rm -rf _build
cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release
cmake --build _build --config Release
cd ..
for files in "$1/_build/Day*/Day*"
do
    for file in $files
    do
        echo $file
        ./$file
    done
done
