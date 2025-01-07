add_executable(nile_app
    app.cpp
)

target_include_directories(nile_app PUBLIC
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(nile_app nile_core)

