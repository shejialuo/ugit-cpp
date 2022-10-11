add_subdirectory(./cli)
add_subdirectory(./data)

add_executable(ugit main.cpp)
target_link_libraries(ugit PRIVATE cli CLI11::CLI11)

# Send the ugit to the top level for using.
set_target_properties(ugit PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/)
