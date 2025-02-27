
# Add executable target
add_executable(${PROJECT_NAME}
    main.cpp
    application/application.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)


# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OpenGL::GL
        glfw
        imgui::imgui
        Async++
        # stringencoders::modp_b64
        CesiumAsync
        CesiumIonClient
        CesiumGeometry
        CesiumGeospatial
        CesiumGltf
        CesiumRasterOverlays
        CesiumUtility
        CesiumJsonReader
        CesiumJsonWriter
        tinyxml2::tinyxml2
        glm::glm
        # ${earcut_target} # Use the resolved earcut target
)

# Copy runtime dependencies on Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
    )
endif()