#include "application/application.hpp"
#include <iostream>
#include <imgui.h>

Application::Application(int width, int height, const std::string &title)
    : window(nullptr), should_close(false), show_demo_window(true), show_hello_world(true), checkbox_value(false), slider_value(0.5f), window_width(width), window_height(height), window_title(title)
{
    init();
}

Application::~Application()
{
    cleanup();
}

void Application::glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void Application::init()
{
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Application::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Application::update()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                should_close = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("Hello World Window", &show_hello_world);
    ImGui::Text("Hello, World!");

    if (ImGui::Button("Close"))
    {
        show_hello_world = false;
    }

    ImGui::Checkbox("Checkbox", &checkbox_value);
    ImGui::SliderFloat("Slider", &slider_value, 0.0f, 1.0f);

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::MenuItem("Close Window"))
        {
            show_hello_world = false;
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void Application::render()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void Application::run()
{
    while (!glfwWindowShouldClose(window) && !should_close)
    {
        update();
        render();
    }
}