cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(NaiveInstruments VERSION 1.0)


FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

FIND_PACKAGE( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR})

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/portaudio")
# find_package( PortAudio REQUIRED )

INCLUDE_DIRECTORIES( "/usr/local/Cellar/portaudio/19.7.0/include" )


add_executable(
  NaiveInstruments
  src/main.cpp
  src/cli/CommandLineArguments.cpp
  src/core/Signal.cpp
  src/file-io/piping.cpp
  src/file-io/record.cpp
  src/instruments/Add.cpp
  src/instruments/BreakpointEnvelope.cpp
  src/instruments/ControlString.cpp
  src/instruments/Multiply.cpp
  src/parsing/LazyRegex.cpp
  src/parsing/NumberPatterns.cpp
  src/parsing/NumberWithUnit.cpp
  src/parsing/Parse.cpp
  src/parsing/RegularExpressionSources.cpp
  src/parsing/Units.cpp
  src/playback/BufferedPlayback.cpp
)

TARGET_LINK_LIBRARIES( NaiveInstruments LINK_PUBLIC "/usr/local/Cellar/portaudio/19.7.0/lib/libportaudio.dylib" )

TARGET_LINK_LIBRARIES( NaiveInstruments LINK_PUBLIC ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES( NaiveInstruments LINK_PUBLIC ${CURSES_LIBRARIES} )

target_include_directories(NaiveInstruments PUBLIC dependencies)

