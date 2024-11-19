#!/bin/bash

# Count amount of parameters, if zero ask for which day to run
if [ "$#" -ne 2 ]; then
    echo "Usage of this script is for instance './run_aoc_day.sh Day01 2024' to run day 1 of 2024"
    exit
fi

cd $2
rm -rf _build/$1
cmake -H. -B_build -DCMAKE_BUILD_TYPE=Debug -DAOC_DAY=$1
cmake --build _build --config Debug
cd ..
./$2/_build/$1/$1
