PROJECT(small_world)

# Using 3.16 because i don't want to have to get the cusom repository
# and it is much easier to just apt-get install cmake
cmake_minimum_required(VERSION 3.16)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_C_STANDARD 17)

# Our output dir
set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR})

# We technically don't need this since we aren't building with VS but better safe than sorry...
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(
    "include"
    "include/thirdparty"
    "data/rooms"
    "src"
)

add_subdirectory(src)
add_subdirectory(data)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data/rooms/)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/logs)

file(COPY ${ROOMS_TO_COPY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/rooms/)

target_precompile_headers(dSmallWorld PRIVATE "include/thirdparty/picojson.h")
