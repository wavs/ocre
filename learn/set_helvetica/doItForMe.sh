#!/bin/sh

cd bmp

for i in *.bmp
do
    ./../binarize $i
done

cat *.txt > ../set_helvetica.txt

rm *.txt