#!/bin/bash
read -r olddir<<<"$1"
read -r newname<<<"$2"

IFS='/' read -r dir oldname <<<"$olddir"

if [ "$dir" != "core" -a "$dir" != "alg" ];
then
  echo "This is a script to raname a directory in logg file"
  echo "Usage: ./renamedir core/oldname newname"
  echo "same with alg"
  echo "Error: destination must be only in alg or core directories"
  exit 1
fi

mv $dir/$oldname $dir/$newname
mv include/$dir/$oldname include/$dir/$newname
