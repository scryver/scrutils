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
#include "Scryver/Math/Transform3D.hpp"


static const std::string vertexFile = "build/resources/shaders/ogldev.vs";
static const std::string fragmentFile = "build/resources/shaders/ogldev.fs";
static const std::string skyBoxVertexFile = "build/resources/shaders/skybox.vs";
static const std::string skyBoxFragmentFile = "build/resources/shaders/skybox.fs";

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

    Scryver::Math::Vector3Df vertices[4];
    vertices[0] = Scryver::Math::Vector3Df(-1.0f, -1.0f, 0.0f);
    vertices[1] = Scryver::Math::Vector3Df( 0.0f, -1.0f, 1.0f);
    vertices[2] = Scryver::Math::Vector3Df( 1.0f, -1.0f, 0.0f);
    vertices[3] = Scryver::Math::Vector3Df( 0.0f,  1.0f, 0.0f);

    Scryver::OpenGL::buffer_t VBO = glManager.createBuffer();
    glManager.bindArrayBuffer(VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glManager.unbindArrayBuffer();

    uint8_t indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    Scryver::OpenGL::buffer_t IBO = glManager.createBuffer();
    glManager.bindElementBuffer(IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glManager.unbindElementBuffer();

    Scryver::OpenGL::vertexArray_t VAO = glManager.createVertexArray();
    glManager.bindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glManager.bindArrayBuffer(VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glManager.unbindArrayBuffer();
    glDisableVertexAttribArray(0);
    glManager.unbindVertexArray();


    Scryver::OpenGL::uniform_t worldLoc = shader.getUniform("world");

    float count = 0.0f;
    Scryver::Math::Transform3Df transform;

    Scryver::OpenGL::texture_t skyBox = glManager.createSkyBox("resources/textures/cubemaps/stairs_in_forest");
    Scryver::Math::Vector3Df skyboxVertices[] = {
        // Positions
        Scryver::Math::Vector3Df(-1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f, -1.0f),

        Scryver::Math::Vector3Df(-1.0f, -1.0f,  1.0f),
        Scryver::Math::Vector3Df(-1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df(-1.0f, -1.0f,  1.0f),

        Scryver::Math::Vector3Df( 1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f, -1.0f),

        Scryver::Math::Vector3Df(-1.0f, -1.0f,  1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f,  1.0f),
        Scryver::Math::Vector3Df(-1.0f, -1.0f,  1.0f),

        Scryver::Math::Vector3Df(-1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f,  1.0f),
        Scryver::Math::Vector3Df(-1.0f,  1.0f, -1.0f),

        Scryver::Math::Vector3Df(-1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f, -1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f, -1.0f),
        Scryver::Math::Vector3Df(-1.0f, -1.0f,  1.0f),
        Scryver::Math::Vector3Df( 1.0f, -1.0f,  1.0f)
    };
    Scryver::OpenGL::buffer_t skyBoxBuf = glManager.createBuffer();
    glManager.bindArrayBuffer(skyBoxBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glManager.unbindArrayBuffer();

    Scryver::OpenGL::vertexArray_t skyBoxVAO = glManager.createVertexArray();
    glManager.bindVertexArray(skyBoxVAO);
    glEnableVertexAttribArray(0);
    glManager.bindArrayBuffer(skyBoxBuf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glManager.unbindArrayBuffer();
    glDisableVertexAttribArray(0);
    glManager.unbindVertexArray();
    Scryver::OpenGL::Shader skyBoxShader;
    if (skyBoxShader.initialize(skyBoxVertexFile, skyBoxFragmentFile) == false)
    {
        shader.destroy();
        glManager.destroy();
        window.destroy();
        return -1;
    }
    // Scryver::OpenGL::uniform_t skyboxMapper = skyBoxShader.getUniform("skybox");

    while (window.isOpen())
    {
        float dt = gameClock.newFrame();
        count += dt;
        float scale = 0.5f * sinf(count * 0.1f) + 0.5f;
        transform.scale(scale, scale, scale);
        transform.worldPos(sinf(count), 0.0f, 0.0f);
        transform.rotate(count * 50.0f, count * 50.0f, count * 50.0f);

        window.pollEvents();
        // if (window.isKeyPressed(Scryver::Keys::Number_1))
        //     debugPrint("Keyboard: Number 1");
        // if (window.isKeyPressed(Scryver::Keys::Space))
        //     debugPrint("Keyboard: Space");
        if (window.isKeyPressed(Scryver::Keys::Escape))
            window.close();

        window.clear();

        skyBoxShader.use();
        glActiveTexture(GL_TEXTURE0);
        glManager.bindSkyBox(skyBox);
        glManager.bindVertexArray(skyBoxVAO);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisableVertexAttribArray(0);
        glManager.unbindVertexArray();

        shader.use();
        glUniformMatrix4fv(worldLoc, 1, GL_TRUE, &transform.get().m[0][0]);
        // Drawing calls
        glManager.bindVertexArray(VAO);
        glManager.bindElementBuffer(IBO);
        glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, 0);
        glDisableVertexAttribArray(0);
        glManager.unbindElementBuffer();
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
