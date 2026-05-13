cmake_minimum_required(VERSION 3.15)
project(number-sorter VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug or Release)" FORCE)
endif()

add_executable(number-sorter hello.c)

target_compile_options(number-sorter PRIVATE
	-Wall
	-Wextra
	-Wpedantic
	$<$<CONFIG:Debug>:	 -g -O0 -DDEBUG>
	$<$<CONFIG:Release>: -O2 -DNDEBUG>
)
