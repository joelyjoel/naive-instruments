#! /usr/local/bin/bash

outputDirectory="most-recent-test-results"
stableTestResults="stable-test-results"


rm -rf "$outputDirectory"
mkdir -p "$outputDirectory"

for testScript in tests/*.sh ; do
  absoluteScriptPath="$(pwd)/$testScript"
  logs=$(
    cd $outputDirectory && $absoluteScriptPath 2> /dev/null
  ) 
done


passed=()
missing=()
failed=()
created=()
count=0

for stableFile in $stableTestResults/* ; do
  ((count = count + 1))
  filename=$(basename "$stableFile")
  freshFile="$outputDirectory/$filename"
  if [ -f "$freshFile" ]; then
    ./compare-audio.sh "$stableFile" "$freshFile" > /dev/null
    if [ $? -ne 0 ]; then
      failed+=( "$filename" )
      
    fi
    passed+=( "$filename" )
  else
    missing+=( "$filename" )
  fi
done

for freshFile in $outputDirectory/* ; do 
  filename=$(basename "$freshFile")
  stableVersion="$stableTestResults/$filename"
  if [ -f "$stableVersion" ]; then
    :
  else
    created+=("$filename")
  fi
done




# Print the report
numberOfPassingSamples=${#passed[@]}
if [ $numberOfPassingSamples -ne 0 ]; then
  echo -e "passed:"
  for i in ${!passed[@]}; do
    name=${passed[$i]}
    echo "  - $name"
  done
fi

numberOfMissingSamples=${#missing[@]}
if [ $numberOfMissingSamples -ne 0 ]; then
  echo -e "missing:"
  for i in ${!missing[@]}; do 
    name=${missing[$i]}
    echo "  - $name"
  done
fi

numberOfFailingSamples=${#failed[@]}
if [ $numberOfFailingSamples -ne 0 ]; then 
  echo "failed:"
  for i in ${!failed[@]}; do
    name=${failed[$i]}
    echo "  - $name"
  done
fi


numberOfExtraSamples=${#created[@]}
if [ $numberOfExtraSamples -ne 0 ]; then 
  echo -e "created:"
  for i in ${!created[@]}; do
    name=${created[$i]}
    echo "  - $name"
  done
fi

numberOfProblems=$((numberOfFailingSamples + numberOfMissingSamples))
echo "numberOfProblems: $numberOfProblems"

if [ $numberOfProblems -ne 0 ]; then
  echo "success: false"
  exit 1
else 
  echo "success: true"
  exit 0
fi
