#!/bin/bash

for outer_dir in */; do
    for dir in $outer_dir/*/; do
        if [ -f $dir/Makefile ]; then
            (
            cd $dir
            make clean
            make test
            )
        fi
    done
done
