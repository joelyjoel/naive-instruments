#! /usr/local/bin/bash

# Check that two audio files sound (exactly) the same
# Many thanks to https://superuser.com/a/532223

file1=$1
file2=$2

hash1=$(ffmpeg -loglevel error -i "$file1" -map 0 -f hash -)
hash2=$(ffmpeg -loglevel error -i "$file2" -map 0 -f hash -)

if [ "$hash1" = "$hash2" ]; then
  exit 0
else
  echo -e "Audio files don't match: $file1 != $file2"
  exit 1
fi
