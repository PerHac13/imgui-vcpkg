#include "application/application.hpp"
#include <iostream>

int main()
{
    try
    {
        Application app(1280, 720, "ImGui + GLFW + OpenGL Example");
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}