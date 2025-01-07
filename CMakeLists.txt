# Minimum CMake version required
cmake_minimum_required(VERSION 3.18)

# Project name and version
project(MyVulkanProject VERSION 1.0 LANGUAGES CXX)

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)  # Disable compiler extensions

# Set compiler flags for pedantic error handling (Clang specific)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
  add_compile_options(
    -Wall
    -Wextra
    -Wuninitialized
    -Wdeprecated
    --pedantic
  )
else()
  message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Set the base output directory for all build targets
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/out)

# Set the output directories for the libraries and binaries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# SDL2
if (NOT DEFINED ENV{SDL2_HOME})
  message(FATAL_ERROR "SDL2_HOME environment variable must be set")
else()
  message(VERBOSE SDL2_HOME: $ENV{SDL2_HOME})
endif()

add_subdirectory($ENV{SDL2_HOME})

# IGNORE FOR NOW
# Ensure that required Vulkan package is found
# find_package(Vulkan REQUIRED)

# Add subdirectories for the app and core modules
add_subdirectory(nile/core)
add_subdirectory(nile/app)

