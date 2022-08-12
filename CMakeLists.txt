cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(NaiveInstruments VERSION 1.0)


FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable(NaiveInstruments src/main.cpp)

TARGET_LINK_LIBRARIES( NaiveInstruments LINK_PUBLIC ${Boost_LIBRARIES} )

target_include_directories(NaiveInstruments PUBLIC dependencies)

