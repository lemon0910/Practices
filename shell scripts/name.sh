#!/bin/bash
files=`ls`

for name in $files
do
    if [ ${name##*.} = "cc" ]; then
        echo "/home/lin/DC/code/$name"
    fi
done

