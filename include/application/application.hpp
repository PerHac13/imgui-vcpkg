#pragma once
#include <string>
#include <memory>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <CesiumAsync/AsyncSystem.h>
#include <CesiumIonClient/Connection.h>
#include <CesiumIonClient/Assets.h>

class Application
{
private:
    GLFWwindow *window;
    bool shouldClose;
    int windowWidth;
    int windowHeight;
    std::string windowTitle;

    // Cesium components
    std::shared_ptr<CesiumAsync::AsyncSystem> asyncSystem;
    std::shared_ptr<CesiumAsync::DefaultAssetAccessor> assetAccessor;
    std::shared_ptr<CesiumIonClient::Connection> ionConnection;
    std::vector<CesiumIonClient::Asset> ionAssets;
    std::string ionAccessToken;
    bool assetsLoaded;

    static void errorCallback(int error, const char *description);
    void initWindow();
    void initImGui();
    void initCesium();
    void loadIonAssets();
    void renderUI();

public:
    Application(int width, int height, const std::string &title);
    ~Application();

    void run();
    void update();
    void render();
};