#! /bin/bash

sample="$1"

report=$(cat ./checksums.yaml | yq ".[\"$sample\"]")
stableChecksum=$(echo $report | yq ".checksum")

checksum=$(ffmpeg -loglevel error -i "$sample" -map 0 -f hash -)

if [ $checksum = $stableChecksum ]; then
  exit 0;
fi

if [ $stableChecksum = "null" ]; then
  while true ; do
    echo -e "\nDoes $sample sound correct?"
    read -p "        p(lay), o(pen), y(es), n(o) ► " command

    case $command in 
      "" | "p" | "play")
        play "$sample"
        ;;

      "o" | "open")
        echo "Opening '$sample' with the default sample editor"
        open "$sample"
        ;;

      # TODO: Add option for using naive's built in waveform viewer.

      "n" | "no")
        echo -e "Skipping 'sampleName' for now.."
        break
        ;;

      "y" | "yes")
        yq -i ".[\"$sample\"].checksum = \"$checksum\"" checksums.yaml
        break
        ;;

      *)
        echo -e "Unexpected command: $command"
     esac
    
  done
else
  if [ $stableChecksum != checksum ]; then
    exit 1;
  fi
fi
