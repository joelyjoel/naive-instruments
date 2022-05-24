coreCPPFiles="src/file-io/record.cpp"

default:
	git clean -fd -- snapshots
	g++ -std=c++20 src/file-io/record.cpp src/main.cpp
	./a.out

	./audition-new-files.sh

zx-dicer:
	mkdir -p bin
	rm -rf junk-output
	mkdir junk-output
	g++ -std=c++20 src/apps/zx-dicer.cpp src/cli/CommandLineArguments.cpp -o bin/zx-dicer
	bin/zx-dicer audio-source-files/piano.wav -o junk-output



