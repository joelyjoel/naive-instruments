cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -stdlib=libc++")


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

project(naive VERSION 1.0)


# - Try to find libsndfile
# Once done, this will define
#
#  LIBSNDFILE_FOUND - system has libsndfile
#  LIBSNDFILE_INCLUDE_DIRS - the libsndfile include directories
#  LIBSNDFILE_LIBRARIES - link these to use libsndfile

# Use pkg-config to get hints about paths
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBSNDFILE_PKGCONF sndfile)
endif(PKG_CONFIG_FOUND)

# Include dir
find_path(LIBSNDFILE_INCLUDE_DIR
        NAMES sndfile.h
        PATHS ${LIBSNDFILE_PKGCONF_INCLUDE_DIRS}
        )

# Library
find_library(LIBSNDFILE_LIBRARY
        NAMES sndfile libsndfile-1
        PATHS ${LIBSNDFILE_PKGCONF_LIBRARY_DIRS}
        )

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(LibSndFile  DEFAULT_MSG  LIBSNDFILE_LIBRARY LIBSNDFILE_INCLUDE_DIR)

if(LIBSNDFILE_FOUND)
    set(LIBSNDFILE_LIBRARIES ${LIBSNDFILE_LIBRARY})
    set(LIBSNDFILE_INCLUDE_DIRS ${LIBSNDFILE_INCLUDE_DIR})
endif(LIBSNDFILE_FOUND)

mark_as_advanced(LIBSNDFILE_LIBRARY LIBSNDFILE_LIBRARIES LIBSNDFILE_INCLUDE_DIR LIBSNDFILE_INCLUDE_DIRS)

include(FindPkgConfig)
pkg_search_module(SndFile REQUIRED sndfile)

include_directories(${LIBSNDFILE_INCLUDE_DIRS})

message(STATUS "sndfile include dirs path: ${LIBSNDFILE_INCLUDE_DIRS}")
message(STATUS "sndfile libs path: ${LIBSNDFILE_LIBRARIES}")

# end libsndfile bit (source https://stackoverflow.com/questions/67237224/cannot-link-sndfile-library-to-cmake-project-macos, many thanks)


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
