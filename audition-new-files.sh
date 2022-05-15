#!/bin/bash

files=$(git ls-files --others --exclude-standard -- snapshots)

for file in "$files" ; do 
  echo $file
  play "$file"
done

