#include <cmath>
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
#include "Scryver/Math/Matrix4.hpp"


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

    Scryver::OpenGL::buffer_t VBO = glManager.createBuffer();
    glManager.bindArrayBuffer(VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glManager.unbindArrayBuffer();

    Scryver::OpenGL::vertexArray_t VAO = glManager.createVertexArray();
    glManager.bindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glManager.bindArrayBuffer(VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glManager.unbindArrayBuffer();
    glDisableVertexAttribArray(0);
    glManager.unbindVertexArray();

    shader.use();

    Scryver::OpenGL::uniform_t scaleLoc = shader.getUniform("gScale");
    Scryver::OpenGL::uniform_t worldLoc = shader.getUniform("world");
    float scale = 0.0f;
    Scryver::Math::Matrix4f world;
    world.m[0][0] = 1.0f;   world.m[0][1] = 0.0f;   world.m[0][2] = 0.0f;   world.m[0][3] = 0.0f;
    world.m[1][0] = 0.0f;   world.m[1][1] = 1.0f;   world.m[1][2] = 0.0f;   world.m[1][3] = 0.0f;
    world.m[2][0] = 0.0f;   world.m[2][1] = 0.0f;   world.m[2][2] = 1.0f;   world.m[2][3] = 0.0f;
    world.m[3][0] = 0.0f;   world.m[3][1] = 0.0f;   world.m[3][2] = 0.0f;   world.m[3][3] = 1.0f;

    while (window.isOpen())
    {
        scale += gameClock.newFrame();
        world.m[0][3] = sinf(scale);

        window.pollEvents();
        // if (window.isKeyPressed(Scryver::Keys::Number_1))
        //     debugPrint("Keyboard: Number 1");
        // if (window.isKeyPressed(Scryver::Keys::Space))
        //     debugPrint("Keyboard: Space");
        if (window.isKeyPressed(Scryver::Keys::Escape))
            window.close();

        window.clear();

        glUniform1f(scaleLoc, sinf(scale));
        glUniformMatrix4fv(worldLoc, 1, GL_TRUE, &world.m[0][0]);
        // Drawing calls
        glManager.bindVertexArray(VAO);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        glManager.unbindVertexArray();

        window.display();

        int32_t frames = gameClock.getFrames(1.0f);
        if (frames >= 0.0f)
        {
            debugPrint("Frames: " << frames);
        }
    }

    shader.destroy();
    glManager.destroy();
    window.destroy();

    return 0;
}
