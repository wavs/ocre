#!/bin/sh

cd bmp

for i in *.bmp
do
    ./../binarize $i
done