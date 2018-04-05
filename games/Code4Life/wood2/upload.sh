#!/bin/bash

files=FILES
full_filename=".transition.cpp"

mv $full_filename $full_filename.backup
touch $full_filename

for filename in $(cat $files)
do 
    sed '/^#include "/ d' $filename >> $full_filename
done 
