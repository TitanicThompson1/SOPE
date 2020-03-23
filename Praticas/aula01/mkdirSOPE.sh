#!/bin/sh
for (( counter=1; counter<14; counter++ ))
do
if [ $counter -lt 10 ];
then
mkdir aula0$counter
else
mkdir aula$counter
fi
done