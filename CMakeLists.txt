cmake_minimum_required(VERSION 3.16)
project(test_fribidi)

set(CMAKE_CXX_STANDARD 17)

## if you wanna .so, just delete this
SET(CMAKE_FIND_LIBRARY_SUFFIXES .a)

find_path(FRIBIDI_INCLUDE_DIR
          NAMES fribidi/fribidi.h)

find_library(FRIBIDI_LIBRARY NAMES fribidi)

if (NOT FRIBIDI_LIBRARY)
  message(STATUS "GNU FriBidi not found")
else()
  message(STATUS "Found GNU FriBidi: ${FRIBIDI_LIBRARY}")
  message(STATUS "Found GNU FriBidi path: ${FRIBIDI_INCLUDE_DIR}")
endif (NOT FRIBIDI_LIBRARY)

add_executable(test_fribidi main.cpp)

include_directories(${FRIBIDI_INCLUDE_DIR})
target_link_libraries(test_fribidi ${FRIBIDI_LIBRARY})
## find_library(FRIBIDI_LIBRARY libfribidi lib)
## target_link_libraries(test_fribidi LINK_PUBLIC ${FRIBIDI_LIBRARY})
## target_link_libraries(test_fribidi -lfribidi)
## target_link_libraries(test_fribidi libfribidi.a)
