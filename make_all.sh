#!/bin/bash

indent_output='sed -r s/^/\t/'

for outer_dir in */; do
    for dir in $outer_dir*/; do
        if [ -f $dir/Makefile ]; then
            (
            cd $dir
            echo [$dir]
            make clean | $indent_output
            make test | $indent_output
            )
        fi
    done
done
