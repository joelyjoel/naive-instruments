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

INCLUDE_DIRECTORIES( "/usr/local/Cellar/portaudio/19.7.0/include" )


add_executable(
  naive
  src/main.cpp
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
)

TARGET_LINK_LIBRARIES( naive LINK_PUBLIC "/usr/local/Cellar/portaudio/19.7.0/lib/libportaudio.dylib" )

TARGET_LINK_LIBRARIES( naive LINK_PUBLIC ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES( naive LINK_PUBLIC ${CURSES_LIBRARIES} )

target_include_directories(naive PUBLIC dependencies)
