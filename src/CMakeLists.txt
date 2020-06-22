add_library(tsr STATIC surface.c target.c drawing.c)
target_compile_options(tsr PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(tsr PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tsr PUBLIC ccore::ccore m)
