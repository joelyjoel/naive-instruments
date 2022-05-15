default:
	git clean -fd -- snapshots
	g++ -std=c++20 src/file-io/record.cpp src/main.cpp
	./a.out

	./audition-new-files.sh


