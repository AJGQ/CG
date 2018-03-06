#!/bin/bash

array=("generator plane plane.3d"
"generator box 3 4 5 3 box.3d"
"generator cylinder 1 3 24 10 cylinder.3d"
"generator cone 3 5 24 10 cone.3d"
"generator sphere 1 12 10 sphere.3d"
)

for command in "${array[@]}"
do
    eval $command > /dev/null 2>&1
    if [ $? -eq 0 ]; then
        perl -C -e 'print chr 0x2713'
        echo " " $command
    else
        perl -C -e 'print chr 0x2717'
        echo " " $command
    fi
done
