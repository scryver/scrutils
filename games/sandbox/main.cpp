#include "config.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

#include <SFML/OpenGL.hpp>

#include "Scryver/Inputs/KeyboardCodes.hpp"
#include "Scryver/Engine/Window.hpp"
#include "Scryver/OpenGL/Manager.hpp"
#include "Scryver/OpenGL/Shader.hpp"
#include "Scryver/Timing/GameClock.hpp"
#include "Scryver/Debug/Printer.hpp"
#include "Scryver/Utility/Macros.hpp"

static const std::vector<float> gCubeBufferData = {
    -1.0f,  -1.0f,  -1.0f, // triangle 1 : begin
    -1.0f,  -1.0f,   1.0f,
    -1.0f,   1.0f,   1.0f, // triangle 1 : end

     1.0f,   1.0f,  -1.0f, // triangle 2 : begin
    -1.0f,  -1.0f,  -1.0f,
    -1.0f,   1.0f,  -1.0f, // triangle 2 : end

     1.0f,  -1.0f,   1.0f,
    -1.0f,  -1.0f,  -1.0f,
     1.0f,  -1.0f,  -1.0f,

     1.0f,   1.0f,  -1.0f,
     1.0f,  -1.0f,  -1.0f,
    -1.0f,  -1.0f,  -1.0f,

    -1.0f,  -1.0f,  -1.0f,
    -1.0f,   1.0f,   1.0f,
    -1.0f,   1.0f,  -1.0f,

     1.0f,  -1.0f,   1.0f,
    -1.0f,  -1.0f,   1.0f,
    -1.0f,  -1.0f,  -1.0f,

    -1.0f,   1.0f,   1.0f,
    -1.0f,  -1.0f,   1.0f,
     1.0f,  -1.0f,   1.0f,

     1.0f,   1.0f,   1.0f,
     1.0f,  -1.0f,  -1.0f,
     1.0f,   1.0f,  -1.0f,

     1.0f,  -1.0f,  -1.0f,
     1.0f,   1.0f,   1.0f,
     1.0f,  -1.0f,   1.0f,

     1.0f,   1.0f,   1.0f,
     1.0f,   1.0f,  -1.0f,
    -1.0f,   1.0f,  -1.0f,

     1.0f,   1.0f,   1.0f,
    -1.0f,   1.0f,  -1.0f,
    -1.0f,   1.0f,   1.0f,

     1.0f,   1.0f,   1.0f,
    -1.0f,   1.0f,   1.0f,
     1.0f,  -1.0f,   1.0f
};

static const std::string vertexFile = "build/resources/shaders/sandbox.vs";
static const std::string fragmentFile = "build/resources/shaders/sandbox.fs";

int main(int argc, char* argv[]) {
    gameClock.initialize();

    Scryver::Engine::Window window;
#if defined(USING_GLFW)
    debugPrint("Initializing window for GLFW");
#elif defined(USING_SFML)
    debugPrint("Initializing window for SFML");
#endif

    if (window.initialize(800, 600, "Main") == false)
        return -1;

    // Scryver::OpenGL::GLManager glManager;
    if (glManager.initialize() == false)
    {
        window.destroy();
        return -1;
    }

    Scryver::OpenGL::Shader shader;
    if (shader.initialize(vertexFile, fragmentFile) == false)
    {
        glManager.destroy();
        window.destroy();
        return -1;
    }

    uint32_t buffer;
    glGenBuffers(1, &buffer);
    if (buffer == 0)
    {
        shader.destroy();
        glManager.destroy();
        window.destroy();
        return -1;
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, VECTOR_ARRAY_SIZE(gCubeBufferData),
                 &gCubeBufferData.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    uint32_t vertexAttribs;
    glGenVertexArrays(1, &vertexAttribs);
    if (vertexAttribs == 0)
    {
        glDeleteBuffers(1, &buffer);
        shader.destroy();
        glManager.destroy();
        window.destroy();
        return -1;
    }
    glUseProgram(static_cast<uint32_t>(shader.identifier));

    glBindVertexArray(vertexAttribs);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    uint32_t modelPtr = glGetUniformLocation(static_cast<uint32_t>(shader.identifier), "model");
    float modelMtrx[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            if (i == j)
                modelMtrx[i][j] = 0.1f;
            else
                modelMtrx[i][j] = 0.0f;
        }
    }

    modelMtrx[3][3] = 1.0f;

    glUseProgram(static_cast<uint32_t>(shader.identifier));
    glUniformMatrix4fv(modelPtr, 1, GL_FALSE, &modelMtrx[0][0]);

    // run the main loop
    while (window.isOpen())
    {
        /*float prevFrameTime = */gameClock.newFrame();

        window.pollEvents();
        if (window.isKeyPressed(Scryver::Keys::Number_1))
            debugPrint("Keyboard: Number 1");
        if (window.isKeyPressed(Scryver::Keys::Space))
            debugPrint("Keyboard: Space");
        if (window.isKeyPressed(Scryver::Keys::Escape))
            window.close();
        window.clear();



        glBindVertexArray(vertexAttribs);

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        window.display();

        int32_t frames = gameClock.getFrames(1.0f);
        if (frames >= 0.0f)
        {
            debugPrint("Frames: " << frames);
        }
    }

    glDeleteBuffers(1, &buffer);

    shader.destroy();
    glManager.destroy();
    window.destroy();

    return 0;
}
