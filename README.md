# ImGui GLFW OpenGL Example Project

A modern C++ project template integrating Dear ImGui with GLFW and OpenGL, featuring docking support and CMake build system.

## Prerequisites

- CMake (version 3.15 or higher)
- C++17 compatible compiler
- Git
- vcpkg package manager

## Installation Guide

### 1. Install vcpkg
First, remove any existing vcpkg installation:
```bash
# If installed in home directory
rm -rf ~/vcpkg
# Or if installed in /opt
sudo rm -rf /opt/vcpkg

# Remove system-wide integration
sudo rm -rf /usr/local/share/vcpkg
sudo rm /usr/local/bin/vcpkg

# Clean up user integration
rm -rf ~/.vcpkg
```

Install fresh copy of vcpkg:
```bash
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

# Run the bootstrap script
./bootstrap-vcpkg.sh

# Install system-wide integration (optional)
./vcpkg integrate install
```

### 2. Set Up Environment
Add vcpkg root to your shell configuration (~/.bashrc, ~/.zshrc, etc.):
```bash
echo 'export VCPKG_ROOT="$HOME/vcpkg"' >> ~/.bashrc
source ~/.bashrc
```

### 3. Clone and Build Project
```bash
# Clone the repository
git clone https://github.com/yourusername/imgui-glfw-project.git
cd imgui-glfw-project

# Install dependencies using vcpkg
vcpkg install

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake -B . -S .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build .
```

## Project Structure
```
imgui-glfw-project/
├── .gitignore
├── CMakeLists.txt
├── vcpkg.json
├── cmake/
│   └── FindImGui.cmake
├── include/
│   └── application/
│       └── application.hpp
├── src/
│   ├── main.cpp
│   └── application/
│       └── application.cpp
└── README.md
```

## Troubleshooting

### Common Issues

1. **vcpkg not found**
   ```bash
   # Verify VCPKG_ROOT is set correctly
   echo $VCPKG_ROOT
   
   # Should print your vcpkg installation path
   ```

2. **CMake can't find packages**
   ```bash
   # Verify packages are installed
   vcpkg list
   
   # Should show:
   # imgui[docking-experimental,glfw-binding,opengl3-binding]
   # glfw3
   # opengl
   ```

3. **Build errors related to ImGui docking**
   ```bash
   # Verify imgui installation with docking
   vcpkg remove imgui --recurse
   vcpkg install imgui[docking-experimental,glfw-binding,opengl3-binding]
   ```

4. **OpenGL-related errors**
   ```bash
   # For Ubuntu/Debian
   sudo apt-get install libgl1-mesa-dev xorg-dev
   
   # For Fedora
   sudo dnf install mesa-libGL-devel xorg-x11-server-devel
   ```

### Cleaning Build
```bash
# Remove build directory and rebuild
rm -rf build/
mkdir build
cd build
cmake -B . -S .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

## Dependencies

- Dear ImGui (with docking branch)
- GLFW3
- OpenGL

## Features

- ImGui docking support
- Modern CMake configuration
- GLFW window management
- OpenGL rendering
- Context menu support
- Proper resource management

## License

This project is licensed under the MIT License - see the LICENSE file for details.
