#!/bin/bash
read -r fulldir<<<"$1"


IFS='/' read -r dir name <<<"$fulldir"

if [ "$dir" != "core" -a "$dir" != "alg" ];
then
  echo "This is a script to remove a directory in logg file"
  echo "Usage: ./remove core/name"
  echo "same with alg"
  echo "Error: destination must be only in alg or core directories"
  exit 1
fi

rm -r $fulldir
rm -r include/$fulldir
