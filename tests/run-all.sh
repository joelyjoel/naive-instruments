{
  cd $(dirname $0)
  referenceToneLocation="../reference-tones"

  for file in *.test.sh ; do
    bash $file
  done


  mkdir -p "$referenceToneLocation"
  for sample in *.wav ; do
    mv "$sample" "$referenceToneLocation"
  done

  source "./checkaudio.sh"
  for sample in $referenceToneLocation/*.wav ; do 
    checkaudio "$sample" || exit 1
  done
}
