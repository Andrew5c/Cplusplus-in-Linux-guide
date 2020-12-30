#!/bin/bash

# make clean for useless files
 
echo "------make clean-------"
cd code/operatorOverload/ 
make clean

cd ../abstractClass/ 
make clean

cd ../binaryTreeClass/
make clean

echo "------add files-------"
# back to main pwd
cd ../..
git add git.sh
git add readme.md
git add doc/*.md
git add doc/fig/*
git add code/LC/*.cpp *.h
git add code/essential/*.cpp *.h

# project files in each chapter of essential
git add code/operatorOverload/
git add code/abstractClass/
git add code/binaryTreeClass/
git add code/binaryTreeClass-2/
git add code/sortAlgorithm/
git add code/cmakeDemo/
git add code/DSAA/

# add the DIY 2048 project
git add fun_2048/src/
git add fun_2048/2048_note.md 
git add fun_2048/CMakeLists.txt 
echo "------add finished-------"


if (($# == 0))
then
 git commit -m "modify files in LINUX"
else
 git commit -m "$1"
fi

echo "-------start push-------"
git push origin master

echo "------ push finished-------"

