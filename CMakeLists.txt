cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -stdlib=libc++")


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(naive VERSION 1.0)


FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

FIND_PACKAGE( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIR})

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/portaudio")
# find_package( PortAudio REQUIRED )

INCLUDE_DIRECTORIES( "/opt/homebrew/Cellar/portaudio/19.7.0/include" )


set(NaiveSourcFiles 
  src/file-io/record.cpp 
  src/core/Signal.cpp 
  src/playback/BufferedPlayback.cpp 
  src/parsing/Parse.cpp 
  src/parsing/LazyRegex.cpp 
  src/parsing/NumberPatterns.cpp 
  src/parsing/Units.cpp 
  src/parsing/NumberWithUnit.cpp 
  src/instruments/Add.cpp 
  src/instruments/Multiply.cpp 
  src/instruments/BreakpointEnvelope.cpp 
  src/instruments/ControlString.cpp 
  src/file-io/piping.cpp 
  src/parsing/RegularExpressionSources.cpp
  src/instruments/Rhythm.cpp
  src/cli/SignalString.cpp
  src/instruments/Osc.cpp
)


add_executable(
  naive
  src/main.cpp
  ${NaiveSourcFiles}
)

TARGET_LINK_LIBRARIES( naive LINK_PUBLIC "/opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.dylib" )

TARGET_LINK_LIBRARIES( naive LINK_PUBLIC ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES( naive LINK_PUBLIC ${CURSES_LIBRARIES} )

target_include_directories(naive PUBLIC dependencies)
 add_executable(
   test_naive
   src/catch-config.test.cpp 
   ${NaiveSourcFiles}
   # TODO: It actually probably is a bit safer to use a glob here
   src/generative/Random.test.cpp 
   src/instruments/BreakpointEnvelope.test.cpp 
   src/instruments/ControlString.test.cpp 
   src/parsing/LazyRegex.test.cpp 
   src/parsing/NumberPatterns.test.cpp 
   src/parsing/NumberWithUnit.test.cpp 
   src/core/Signal.test.cpp 
   src/core/Sample.test.cpp
   src/parsing/parse.test.cpp 
   src/parsing/RegularExpressionSources.test.cpp 
   src/parsing/Units.test.cpp
 )
TARGET_LINK_LIBRARIES( test_naive LINK_PUBLIC ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES( test_naive LINK_PUBLIC ${CURSES_LIBRARIES} )
TARGET_LINK_LIBRARIES( test_naive LINK_PUBLIC "/opt/homebrew/Cellar/portaudio/19.7.0/lib/libportaudio.dylib" )
