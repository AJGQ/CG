#!/bin/bash

array=("generator plane plane.3d"
"generator box box.3d 3 4 5 10"
"generator cylinder cylinder.3d 3 5 24"
"generator cone cone.3d 3 5 24 10"
"generator sphere sphere.3d 4 24 24"
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
