cmake_minimum_required(VERSION 3.15)
project(imgui_glfw_project VERSION 1.0.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Async++ CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

include(FetchContent)

# Fetch Cesium Native
FetchContent_Declare(
    cesium
    GIT_REPOSITORY https://github.com/CesiumGS/cesium-native.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cesium)

# Try vcpkg ImGui first, fallback to FindImGui.cmake if not found
find_package(imgui CONFIG)
if(NOT imgui_FOUND)
    find_package(ImGui REQUIRED)
endif()

# Add subdirectories for source files
add_subdirectory(src)