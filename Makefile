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

default: main
all: main build-and-run-tests  

#TODO: A big utility for namespacing all other utilities

main:
	mkdir -p bin
	g++ ${FLAGS} \
		src/file-io/record.cpp \
		src/playback/BufferedPlayback.cpp \
		src/parsing/Parse.cpp \
		src/main.cpp -o bin/ni

build-and-run-tests:
	git clean -fd -- snapshots
	g++ ${FLAGS} src/file-io/record.cpp src/snapshot-tests.cpp -o src/snapshot-tests.bin
	src/snapshot-tests.bin

tests:
	g++ ${FLAGS} src/**/*.test.cpp -o bin/unit-tests

test: tests
	bin/unit-tests



#TODO: concat - join samples together with crossfades
#TODO: envelope - create flexible control signals
#TODO: AHD - simple Attack Hold Decay envelopes

