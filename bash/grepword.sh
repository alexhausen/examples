#!/bin/bash

if [ $# -lt 2 ]; then
  echo "usage: grepword.sh <regex> file.doc"
  exit 1
fi

#avoid files with spaces problem
IFS=$(echo -en "\n\b")

regex=""
for file in "$@"; do
  if [ "$regex"  == "" ]; then
    regex="$file"
    continue
  fi

  if [ -f "$file" ]; then
#    result=`antiword "$file" | ag $regex`
    result=`catdoc "$file" | ag $regex`
    if [ $? -eq 0 ] && [ "$result" != "" ]; then  
      echo -en "\e[0;49;32m$file\e[0m:\n$result\n" 
    fi
  fi

done