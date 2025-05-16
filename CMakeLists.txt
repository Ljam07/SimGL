cmake_minimum_required(VERSION 3.10)

project(SimGL VERSION 0.1.0 LANGUAGES C CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------------
# 1) Gather your sources (your .cpp files only)
# ----------------------------------------------------------------------------
file(GLOB_RECURSE SIMGL_CPP_SOURCES
    "${CMAKE_SOURCE_DIR}/Engine/*.cpp"
    "${CMAKE_SOURCE_DIR}/Playground/*.cpp"
)

# ----------------------------------------------------------------------------
# 2) Create a GLAD static library
# ----------------------------------------------------------------------------
add_library(glad STATIC
    "${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c"
)

# Force the linker language to C (so CMake knows which linker to use)
set_target_properties(glad PROPERTIES
    LINKER_LANGUAGE C
)

target_include_directories(glad
    PUBLIC
        "${CMAKE_SOURCE_DIR}/vendor/glad/include"
)


# ----------------------------------------------------------------------------
# 3) Your main executable
# ----------------------------------------------------------------------------
add_executable(SimGL
    ${SIMGL_CPP_SOURCES}
    "${CMAKE_SOURCE_DIR}/main.cpp"
)

# ----------------------------------------------------------------------------
# 4) Include paths
# ----------------------------------------------------------------------------
target_include_directories(SimGL PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/vendor/glm/include"           # header‐only
    "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"  # your prebuilt GLFW
)

# ----------------------------------------------------------------------------
# 5) Link order: first GLAD, then GLFW, then OpenGL
# ----------------------------------------------------------------------------
target_link_libraries(SimGL
    PRIVATE
        glad                                  # our static lib from above
        #--- find your GLFW .lib/.a with find_library or hardcode path ---#
        "${CMAKE_SOURCE_DIR}/vendor/GLFW/lib/libglfw3.a"  # or .a on MinGW
        OpenGL::GL                           # from find_package below
)

# ----------------------------------------------------------------------------
# 6) Make sure OpenGL is found
# ----------------------------------------------------------------------------
find_package(OpenGL REQUIRED)
# (OpenGL::GL is already in the link‐line above)

# ----------------------------------------------------------------------------
# 7) GLFW context hints and linking extras
# ----------------------------------------------------------------------------
# If you’re on Linux you may need X11, pthread, dl, etc.
# If on Windows with MinGW your .lib above is enough.

# ----------------------------------------------------------------------------
# 8) Install and other goodies…
# ----------------------------------------------------------------------------
