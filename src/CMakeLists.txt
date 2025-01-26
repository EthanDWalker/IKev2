# Collect all .c files in this directory and subdirectories
file(GLOB_RECURSE SRC_FILES "*.c")

# Add the executable target
add_executable(VPNServer ${SRC_FILES})

# Link the corresponding header directory
target_include_directories(VPNServer PRIVATE ${INCLUDE_DIR})
