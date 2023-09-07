#! /bin/bash

function checkaudio {
  touch ./checksums.yaml

  sample="$1"

  report=$(cat ./checksums.yaml | yq ".[\"$sample\"]")
  stableChecksum=$(echo $report | yq ".checksum")

  checksum=$(ffmpeg -loglevel error -i "$sample" -map 0 -f hash -)

  if [ $checksum = $stableChecksum ]; then
    echo -e " ✅ $sample is correct."
    return 0;
  fi

  if [ $stableChecksum = "null" ]; then
    while true ; do
      echo -e "\n ❓ Does $sample sound correct?"
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
          echo -e " ✅ $sample confirmed by user.\n"
          break
          ;;

        *)
          echo -e "Unexpected command: $command"
       esac
      
    done
  else
    if [ $stableChecksum != checksum ]; then
      return 1;
    fi
  fi
}
