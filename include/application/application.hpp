#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <string>

class Application
{
public:
    Application(int width, int height, const std::string &title);
    ~Application();

    void run();

private:
    void init();
    void cleanup();
    void update();
    void render();
    static void glfw_error_callback(int error, const char *description);

    GLFWwindow *window;
    bool should_close;

    // ImGui state
    bool show_demo_window;
    bool show_hello_world;
    bool checkbox_value;
    float slider_value;

    const int window_width;
    const int window_height;
    const std::string window_title;
};