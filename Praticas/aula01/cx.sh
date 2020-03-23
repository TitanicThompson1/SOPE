#!/bin/sh
read filename
rm $filename
gcc -Wall -o $filename $filename.c
if [ $? -eq 0 ];
then
./$filename
else
echo "COMPILATION ERROR"
fi