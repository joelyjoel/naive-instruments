CC=g++

FLAGS=-I ../include\
			-I ../vendor/include\
			-Wc++11-extensions\
			-std=c++14\
			-stdlib=libc++\
			-fPIC\
			-isystem /usr/local/include\
			-isystem /Library/Developer/CommandLineTools/usr/bin/../include/c++/v1\
			-isystem /Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include\
			-isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include\
			-isystem /Library/Developer/CommandLineTools/usr/include\
			-isystem /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks\
			-I ./deps\
			-L ./deps\
			-l portaudio\
			-framework CoreServices\
			-framework CoreFoundation\
			-framework AudioUnit\
			-framework AudioToolbox\
			-framework CoreAudio\
			-g



default:
	${CC} ${flags} src/*.cpp
