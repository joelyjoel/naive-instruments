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

CPP_SOURCE_FILES=src/file-io/record.cpp \
								 src/core/Signal.cpp \
								 src/playback/BufferedPlayback.cpp \
								 src/parsing/Parse.cpp \
								 src/parsing/LazyRegex.cpp \
								 src/parsing/NumberPatterns.cpp \
								 src/parsing/Units.cpp \
								 src/parsing/NumberWithUnit.cpp \
								 src/instruments/Add.cpp \
								 src/instruments/Multiply.cpp \
								 src/instruments/BreakpointEnvelope.cpp \
								 src/instruments/ControlString.cpp \
								 src/file-io/piping.cpp \
								 src/parsing/RegularExpressionSources.cpp

FLAGS=-std=c++20 \
			-I ./dependencies -L ./dependencies \
			-l boost_program_options \
			${NCURSES_FLAGS} \
			${PORTAUDIO_FLAGS}

default: main
all: main build-and-run-tests  

#TODO: A big utility for namespacing all other utilities

main:
	mkdir -p bin
	g++ ${FLAGS} \
		${CPP_SOURCE_FILES} \
		src/main.cpp -o bin/naive
	# For sentimental/legacy reasons
	cp bin/naive bin/malc

debug:
	mkdir -p bin
	g++ ${FLAGS} \
		${CPP_SOURCE_FILES} \
		-g \
		src/main.cpp -o bin/malc

build-and-run-tests:
	git clean -fd -- snapshots
	g++ ${FLAGS} src/file-io/record.cpp src/snapshot-tests.cpp -o src/snapshot-tests.bin
	src/snapshot-tests.bin

unit-tests:
	g++ ${FLAGS} src/**/*.test.cpp src/*.test.cpp ${CPP_SOURCE_FILES} -o bin/unit-tests

test: unit-tests
	bin/unit-tests

readme:
	bash docs/readme.sh > README.md


#TODO: concat - join samples together with crossfades
#TODO: envelope - create flexible control signals
#TODO: AHD - simple Attack Hold Decay envelopes

