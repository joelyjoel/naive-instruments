#! /usr/local/bin/bash

outputDirectory=$1

if [ -z "$outputDirectory" ] ;  then
  outputDirectory="most-recent-test-results"
  rm -rf $outputDirectory
fi


mkdir -p $outputDirectory

for testScript in tests/*.sh ; do
  absoluteScriptPath="$(pwd)/$testScript"
  (
    cd $outputDirectory && $absoluteScriptPath
  )
done
