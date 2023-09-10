{
  cd $(dirname $0)

  for file in *.test.sh ; do
    bash $file
  done


  mkdir -p results
  for sample in *.wav ; do
    mv "$sample" results
  done

  source "./checkaudio.sh"
  for sample in results/*.wav ; do 
    checkaudio "$sample" || exit 1
  done
}
