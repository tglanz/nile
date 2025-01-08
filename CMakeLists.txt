cmake_minimum_required(VERSION 3.18)

project(Nile VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

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

# Vulkan
# Fuck Mac: https://vulkan.lunarg.com/doc/sdk/1.3.296.0/mac/getting_started.html

add_subdirectory(submodules/SDL)
include_directories(PRIVATE submodules/SDL/include)

set(SPDLOG_BUILD_SHARED ON CACHE BOOL "" FORCE)
add_subdirectory(submodules/spdlog)
include_directories(PRIVATE submodules/spdlog/include)

# IGNORE FOR NOW
# Ensure that required Vulkan package is found
# find_package(Vulkan REQUIRED)

file(GLOB_RECURSE app_sources "${PROJECT_SOURCE_DIR}/nile/app/*.hpp" "${PROJECT_SOURCE_DIR}/nile/app/*.cpp")
message("App sources: ${app_sources}")
add_executable(nile_app ${app_sources})
target_include_directories(nile_app PRIVATE "${PROJECT_SOURCE_DIR}")
target_link_libraries(nile_app SDL2 spdlog)
