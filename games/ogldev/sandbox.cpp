#include <cstdint>
#include <string>
#include <vector>

#include <GL/glew.h>

#include "Scryver/Inputs/KeyboardCodes.hpp"
#include "Scryver/Engine/Window.hpp"
#include "Scryver/OpenGL/Manager.hpp"
#include "Scryver/OpenGL/Shader.hpp"
#include "Scryver/Timing/GameClock.hpp"
#include "Scryver/Debug/Printer.hpp"
#include "Scryver/Utility/Macros.hpp"
#include "Scryver/Math/Vector3D.hpp"


static const std::string vertexFile = "build/resources/shaders/ogldev.vs";
static const std::string fragmentFile = "build/resources/shaders/ogldev.fs";

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

    Scryver::Math::Vector3Df vertices[3];
    vertices[0] = Scryver::Math::Vector3Df(-1.0f, -1.0f, 0.0f);
    vertices[1] = Scryver::Math::Vector3Df(1.0f, -1.0f, 0.0f);
    vertices[2] = Scryver::Math::Vector3Df(0.0f, 1.0f, 0.0f);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glUseProgram(shader.identifier);

    while (window.isOpen())
    {
        gameClock.newFrame();

        window.pollEvents();
        // if (window.isKeyPressed(Scryver::Keys::Number_1))
        //     debugPrint("Keyboard: Number 1");
        // if (window.isKeyPressed(Scryver::Keys::Space))
        //     debugPrint("Keyboard: Space");
        if (window.isKeyPressed(Scryver::Keys::Escape))
            window.close();

        window.clear();

        // Drawing calls
        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);

        window.display();

        int32_t frames = gameClock.getFrames(1.0f);
        if (frames >= 0.0f)
        {
            debugPrint("Frames: " << frames);
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.destroy();
    glManager.destroy();
    window.destroy();

    return 0;
}
