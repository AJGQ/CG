#!/bin/bash

array=("generator plane plane.3d"
"generator box 3 4 5 3 box.3d"
"generator inv_box 3 4 5 3 inv_box.3d"
"generator cylinder 1 3 96 500 cylinder.3d"
"generator cone 3 5 48 5 cone.3d"
"generator sphere 1 48 48 sphere.3d"
"generator inv_sphere 1 48 48 inv_sphere.3d"
"generator torus 1 0.5 48 48 torus.3d"
"generator bezier teapot.patch 4 teapot.3d"
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
