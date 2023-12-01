#!/bin/bash

# Count amount of parameters, if zero ask for which day to run


cd $2
cmake -H. -B_build -DCMAKE_BUILD_TYPE=Debug -DAOC_DAY=$1
cmake --build _build --config Debug
cd ..
./$2/_build/$1/$1
