coreCPPFiles="src/file-io/record.cpp"

default: rms-graph build-and-run-tests rms-graph getch-log

build-and-run-tests:
	git clean -fd -- snapshots
	g++ -std=c++20 src/file-io/record.cpp src/main.cpp
	./a.out


zx-dicer:
	mkdir -p bin
	rm -rf junk-output
	mkdir junk-output
	g++ -std=c++20 src/apps/zx-dicer.cpp -o bin/zx-dicer
	bin/zx-dicer audio-source-files/piano.wav -o junk-output

zx-select:
	mkdir -p bin
	g++ -std=c++20 src/apps/zx-select.cpp -o bin/zx-select

rms-graph:
	mkdir -p bin
	g++ -std=c++20 src/apps/rms-graph.cpp -o bin/rms-graph

getch-log:
	mkdir -p bin
	g++ -std=c++20 -D_XOPEN_SOURCE_EXTENDED -lncurses src/apps/getch-log.cpp -o bin/getch-log
