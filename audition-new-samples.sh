#! /bin/bash

# Interactive script for auditioning new samples created by tests and adding
# them to the stable-pack if they pass review.

report=$(./run-tests.sh)
# toReview=$(echo "$report" | yq '.created[]')
readarray -t toReview <<<$(echo "$report" | yq '.created[]')
stablePackDir=$(echo "$report" | yq '.stablePack')


if [ -z "$toReview" ]; then 
  echo "Nothing to review!"
  exit 0
fi

count=${#toReview[@]}
# i=0
for i in ${!toReview[@]} ; do 
  # ((i=i+1))
  sample="${toReview[$i]}"
  sampleName=$(basename "$sample")

  while true ; do
    echo -e "\n[$i/$count] Should '$sampleName' be added to the stable-pack?"
    read -p "        p(lay), o(pen), y(es), n(o) ► " command

    case $command in 
      "" | "p" | "play")
        play "$sample"
        ;;

      "o" | "open")
        echo "Opening '$sampleName' with the default sample editor"
        open "$sample"
        ;;

      # TODO: Add option for using naive's built in waveform viewer.

      "n" | "no")
        echo -e "Skipping 'sampleName' for now.."
        break
        ;;

      "y" | "yes")
        echo -e "Copying $sample -> $stablePackDir\n"
        # cp "$sample" "$stablePackDir"
        checksum=$(ffmpeg -loglevel error -i "$sample" -map 0 -f hash -)
        echo "checksum $checksum"

        yq -i ".[\"$sampleName\"].checksum = \"$checksum\"" checksums.yaml
        break
        ;;

      *)
        echo -e "Unexpected command: $command"
     esac
  done
done

echo "   All done!"
