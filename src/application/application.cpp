#include "application/application.hpp"
#include <iostream>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Application::Application(int width, int height, const std::string &title)
    : windowWidth(width), windowHeight(height), windowTitle(title),
      shouldClose(false), assetsLoaded(false)
{
    initWindow();
    initImGui();
    initCesium();
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::errorCallback(int error, const char *description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void Application::initWindow()
{
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Application::initImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
void Application::initCesium()
{
    try
    {
        asyncSystem = std::make_shared<CesiumAsync::AsyncSystem>();
        assetAccessor = std::make_shared<CesiumAsync::DefaultAssetAccessor>();
        CesiumIonClient::ApplicationData appData{
            "Simple Cesium Renderer",
            "1.0.0"};

        const char *token = std::getenv("CESIUM_ION_TOKEN");
        if (!token)
        {
            throw std::runtime_error("CESIUM_ION_TOKEN environment variable not set");
        }

        ionAccessToken = token;

        ionConnection = std::make_shared<CesiumIonClient::Connection>(
            asyncSystem,
            "Simple Cesium Renderer",
            "1.0.0",
            ionAccessToken);

        std::cout << "Cesium Ion connection initialized successfully.\n";

        loadIonAssets();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error initializing Cesium Ion: " << ex.what() << "\n";
        throw;
    }
}

void Application::loadIonAssets()
{
    if (!ionConnection)
    {
        std::cerr << "Ion connection is not initialized. Cannot load assets.\n";
        return;
    }

    ionConnection->assets().thenInMainThread(
                               [this](std::vector<CesiumIonClient::Asset> &&assets)
                               {
                                   try
                                   {
                                       ionAssets = std::move(assets);
                                       assetsLoaded = true;

                                       std::cout << "Successfully loaded " << ionAssets.size() << " assets from Cesium Ion.\n";
                                   }
                                   catch (const std::exception &ex)
                                   {
                                       std::cerr << "Error while processing assets: " << ex.what() << "\n";
                                   }
                               })
        .catchInMainThread(
            [](const std::exception &ex)
            {
                std::cerr << "Error fetching assets from Cesium Ion: " << ex.what() << "\n";
            });
}

void Application::renderUI()
{
    ImGui::Begin("Cesium Ion Assets");

    if (!assetsLoaded)
    {
        ImGui::Text("Loading assets...");
    }
    else
    {
        ImGui::Text("Available Assets:");
        for (const auto &asset : ionAssets)
        {
            if (ImGui::TreeNode(asset.name.c_str()))
            {
                ImGui::Text("ID: %ld", asset.id);
                ImGui::Text("Type: %s", asset.type.c_str());
                ImGui::Text("Description: %s", asset.description.c_str());
                ImGui::TreePop();
            }
        }
    }

    ImGui::End();

    // Demo window for reference
    bool show_demo = true;
    ImGui::ShowDemoWindow(&show_demo);
}

void Application::update()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    renderUI();
}

void Application::render()
{
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void Application::run()
{
    while (!glfwWindowShouldClose(window) && !shouldClose)
    {
        update();
        render();
    }
}