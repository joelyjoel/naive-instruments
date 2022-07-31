#! /usr/local/bin/bash

outputDirectory="most-recent-test-results"
stableTestResults="stable-test-results"

mkdir -p $outputDirectory

for testScript in tests/*.sh ; do
  absoluteScriptPath="$(pwd)/$testScript"
  (
    cd $outputDirectory && $absoluteScriptPath
  )
done


count=0
for stableFile in $stableTestResults/* ; do
  filename=$(basename "$stableFile")
  freshFile="$outputDirectory/$filename"

  if [ -f "$freshFile" ]; then
    ./compare-audio.sh "$stableFile" "$freshFile"
    echo -e "   $filename"
  else
    echo "Missing file: $filename"
    exit 1
  fi

  ((count = count + 1))
  
done

echo "$count tests passed"

