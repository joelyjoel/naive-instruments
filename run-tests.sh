#! /usr/local/bin/bash

# This script will run all the scripts in the tests/* directory which create a
# sample pack, called the 'test-pack'. This newly generated sample pack is then
# compared against the 'stable-pack'. If there are samples in the stable-pack
# which are missing or non-matching in the test-pack then the test is failed.
# Conversely, if there are samples in the test-pack which are not yet present
# in the stable pack then these need to be auditioned/reviewed and added to the
# stable-pack.

# 1. Run the tests, creating the test-pack

testPackDir="$(pwd)/most-recent-test-results"
stablePackDir="$(pwd)/stable-test-results"

rm -rf "$testPackDir"
mkdir -p "$testPackDir"
mkdir -p "$stablePackDir"

for testScript in tests/*.sh ; do
  absoluteScriptPath="$(pwd)/$testScript"
  logs=$(
    cd $testPackDir 
    bash "$absoluteScriptPath" 2> /dev/null
  ) 
done


# 2. Compare test pack to the stable pack

passed=()
missing=()
failed=()
created=()

if [ "$(ls "$stablePackDir")" != "" ]; then
  for stableFile in $stablePackDir/* ; do
    filename=$(basename "$stableFile")
    freshFile="$testPackDir/$filename"
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
fi

for freshFile in $testPackDir/* ; do 
  filename=$(basename "$freshFile")
  stableVersion="$stablePackDir/$filename"
  if [ -f "$stableVersion" ]; then
    :
  else
    created+=("$testPackDir/$filename")
  fi
done




# 3. Generate a report

echo "stablePack: $stablePackDir"
echo "testPack: $testPackDir"

numberOfPassingSamples=${#passed[@]}
if [ $numberOfPassingSamples -ne 0 ]; then
  echo -e "passed:"
  echo "  # Woo! These samples all look correct!"
  for i in ${!passed[@]}; do
    name=${passed[$i]}
    echo "  - $name"
  done
fi

numberOfMissingSamples=${#missing[@]}
if [ $numberOfMissingSamples -ne 0 ]; then
  echo -e "missing:"
  echo "  # These samples exist in the stable-pack, but were missing in the test-pack."
  for i in ${!missing[@]}; do 
    name=${missing[$i]}
    echo "  - $name"
  done
fi

numberOfFailingSamples=${#failed[@]}
if [ $numberOfFailingSamples -ne 0 ]; then 
  echo "failed:"
  echo "  # These samples had non-matching checksums between the stable-pack and the test-pack."
  for i in ${!failed[@]}; do
    name=${failed[$i]}
    echo "  - $name"
  done
fi


numberOfExtraSamples=${#created[@]}
if [ $numberOfExtraSamples -ne 0 ]; then 
  echo -e "created:"
  echo -e "  # These samples need to be auditioned and added to the stable-pack if they pass review."
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
