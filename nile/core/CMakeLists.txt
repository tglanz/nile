add_library(nile_core STATIC
    core.cpp
)

target_include_directories(nile_core PUBLIC
    ${CMAKE_SOURCE_DIR}
)

