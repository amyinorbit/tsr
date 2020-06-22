INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

add_executable(tsr_example main.c)
target_link_libraries(tsr_example PRIVATE tsr ccore::ccore ${SDL2_LIBRARIES})

link_directories("${LINK_DIRECTORIES}" "${SDL2_LIBDIR}")
target_include_directories(tsr_example PRIVATE ${SDL2_INCLUDE_DIRS})

add_custom_target(example_run
    COMMAND $<TARGET_FILE:tsr_example>
    DEPENDS tsr_example
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(example_dbg
    COMMAND lldb $<TARGET_FILE:tsr_example>
    DEPENDS tsr_example
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
