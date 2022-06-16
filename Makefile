coreCPPFiles="src/file-io/record.cpp"

PORTAUDIO_FLAGS=-I ../include\
							  -I ../vendor/include \
								-stdlib=libc++ \
								-fPIC \
								-isystem /usr/local/include \
								-isystem /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1 \
								-isystem /Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include \
								-isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include \
								-isystem /Library/Developer/CommandLineTools/usr/include \
								-isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks  \
								-l portaudio \
								-framework CoreServices \
								-framework CoreFoundation \
								-framework AudioUnit \
								-framework AudioToolbox \
								-framework CoreAudio

NCURSES_FLAGS=-D_XOPEN_SOURCE_EXTENDED -lncurses

FLAGS=-std=c++20 \
			-I ./dependencies -L ./dependencies \
			${NCURSES_FLAGS} \
			${PORTAUDIO_FLAGS}

default: all
all: rms-graph build-and-run-tests zx-select ruler rms-graph getch-log playback-demo ncurses-window-demo slice

#TODO: A big utility for namespacing all other utilities

build-and-run-tests:
	git clean -fd -- snapshots
	g++ ${FLAGS} src/file-io/record.cpp src/snapshot-tests.cpp -o src/snapshot-tests.bin
	src/snapshot-tests.bin

zx-select:
	mkdir -p bin
	g++ ${FLAGS} src/apps/zx-select.cpp -o bin/zx-select

rms-graph:
	mkdir -p bin
	g++ ${FLAGS} src/apps/rms-graph.cpp -o bin/rms-graph

getch-log:
	mkdir -p bin
	g++ ${FLAGS} src/apps/getch-log.cpp -o bin/getch-log

ruler:
	mkdir -p bin
	g++ ${FLAGS} src/apps/ruler.cpp -o bin/ruler

ncurses-window-demo:
	mkdir -p bin
	g++ ${FLAGS} src/apps/ncurses-window-demo.cpp -o bin/ncurses-window-demo


playback-demo:
	mkdir -p bin
	g++ \
		${FLAGS} \
		src/apps/playback-demo.cpp \
		src/playback/BufferedPlayback.cpp \
		-o bin/playback-demo

slice:
	mkdir -p bin
	g++ \
		${FLAGS} \
		src/apps/slice.cpp \
		src/playback/BufferedPlayback.cpp \
		-o bin/slice

#TODO: concat - join samples together with crossfades
#TODO: mix - mix samples together
#TODO: osc - create wavetable tones
#TODO: envelope - create flexible control signals
#TODO: AHD - simple Attack Hold Decay envelopes

