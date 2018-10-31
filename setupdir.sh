#!/bin/bash

IFS='/' read -r topdir string <<< "$1"
if [ $topdir != "core" -a $topdir != "alg"  ]; then
	echo "error, can only accept core/ or alg/"
	exit 1
fi

mkdir $1
mkdir $1/src
mkdir $1/lib
mkdir $1/bin
mkdir $1/doc
mkdir include/$1

cat   <template/CoreMakefile > $1/Makefile
cat   <template/README.md > $1/src/README.md
cat   <template/README.md > $1/lib/README.md
cat   <template/README.md > $1/bin/README.md
cat   <template/README.md > $1/doc/README.md
cat   <template/README.md > include/$1/README.md



