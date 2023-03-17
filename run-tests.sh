
# This script will run all the scripts in the tests/* directory which create a
# sample pack, called the 'test-pack'. This newly generated sample pack is then
# compared against the 'stable-pack'. If there are samples in the stable-pack
# which are missing or non-matching in the test-pack then the test is failed.
# Conversely, if there are samples in the test-pack which are not yet present
# in the stable pack then these need to be auditioned/reviewed and added to the
# stable-pack.

# NOTE: This test script has been optimised to avoid using too much disk space,
# now checksums are stored in checksums.yaml and these are used to test the
# test pack rather than using the stable pack. Its not as cool, but its way
# more performant.


if which naive ; then
  echo "Found naive executable";
else
  echo "Couldn't find naive executable, have you added it to PATH?"
  exit 1
fi

# 1. Run the tests, creating the test-pack

testPackDir="$(pwd)/most-recent-test-results"

rm -rf "$testPackDir"
mkdir -p "$testPackDir"

for testScript in tests/*.sh ; do
  absoluteScriptPath="$(pwd)/$testScript"
  echo "Running $absoluteScriptPath"
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

numberOfChecksums=$(yq "length" checksums.yaml)
for ((i=0;i<$numberOfChecksums;i++)) do 
  filename=$(yq "keys | .$i" checksums.yaml)
  stableChecksum=$(yq ".[\"$filename\"].checksum" checksums.yaml)
  freshFile="$testPackDir/$filename"
  if [ -f "$freshFile" ]; then
    freshChecksum=$(ffmpeg -loglevel error -i "$freshFile" -map 0 -f hash -)
    if [ "$freshChecksum" = "$stableChecksum" ]; then
      passed+=( "$filename" )
    else
      failed+=( "$filename" )
    fi
  else 
    missing+=("$filename")
  fi
done


for freshFile in $testPackDir/* ; do 
  filename=$(basename "$freshFile")
  notInStablePack=$(yq ".[\"$filename\"] == null" checksums.yaml)
  if [ "$notInStablePack" == "true" ]; then
    created+=("$freshFile")
  fi
done


# 3. Generate a report

echo "testPack: $testPackDir"

numberOfPassingSamples=${#passed[@]}
if [ $numberOfPassingSamples -ne 0 ]; then
  :
  # echo -e "passed:"
  # echo "  # Woo! These samples all look correct!"
  # for i in ${!passed[@]}; do
  #   name=${passed[$i]}
  #   echo "  - $name"
  # done
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
  echo "#   All tests passed!"
  exit 0
fi
