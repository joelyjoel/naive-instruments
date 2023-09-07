for file in $(dirname $0)/*.test.sh ; do
  echo "Running $file"
  bash $file
done
