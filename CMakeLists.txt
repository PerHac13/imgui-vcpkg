cmake_minimum_required(VERSION 3.15)
project(imgui_glfw_project VERSION 1.0.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add cmake modules path
# list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# Try vcpkg ImGui first, fallback to FindImGui.cmake if not found
find_package(imgui CONFIG)
if(NOT imgui_FOUND)
    find_package(ImGui REQUIRED)
endif()

# Add subdirectories
add_subdirectory(src)