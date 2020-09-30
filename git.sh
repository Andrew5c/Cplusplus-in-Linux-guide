#!/bin/bash

# make clean for useless files
cd code/operatorOverload/ 
make clean

cd ../abstractClass/ 
make clean

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
git add code/sortAlgorithm/

if (($# == 0))
then
 git commit -m "modify files in LINUX"
else
 git commit -m "$1"
fi

git push origin master

