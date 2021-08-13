#!/bin/bash


for file in `ls test`
do
    ./bashChecker.sh ./hsh test/$file
done
echo
