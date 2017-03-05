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
#include "Scryver/Math/Vector2D.hpp"
#include "Scryver/Math/Vector3D.hpp"
#include "Scryver/Math/Matrix4.hpp"
#include "Scryver/Math/Transform3D.hpp"
#include "Scryver/Render/Camera.hpp"


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

    if (window.initialize(800, 600, "Main", Scryver::Engine::CursorMode::Normal) == false)
        return -1;

    debugPrint(window.size().x << "x" << window.size().y);

    if (glManager.initialize(10, 10, 10, true) == false)
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

    Scryver::Render::Camera camera;
    camera.initialize(Scryver::Math::Vector3Df(0, 0, -5.0f),
                      Scryver::Math::Vector3Df(0, 0, 1),
                      Scryver::Math::Vector3Df(0, 1, 0),
                      800.0f, 600.0f);

    Scryver::OpenGL::uniform_t worldLoc = shader.getUniform("world");
    Scryver::OpenGL::uniform_t cameraLoc = shader.getUniform("camera");

    float count = 0.0f;
    Scryver::Math::Transform3Df transform;

    Scryver::OpenGL::texture_t skyBox = glManager.createSkyBox("resources/textures/cubemaps/stairs_in_forest");
    Scryver::Math::Vector3Df skyboxVertices[] = {
        // Positions
        Scryver::Math::Vector3Df(-50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f, -50.0f),

        Scryver::Math::Vector3Df(-50.0f, -50.0f,  50.0f),
        Scryver::Math::Vector3Df(-50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df(-50.0f, -50.0f,  50.0f),

        Scryver::Math::Vector3Df( 50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f, -50.0f),

        Scryver::Math::Vector3Df(-50.0f, -50.0f,  50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f,  50.0f),
        Scryver::Math::Vector3Df(-50.0f, -50.0f,  50.0f),

        Scryver::Math::Vector3Df(-50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f,  50.0f),
        Scryver::Math::Vector3Df(-50.0f,  50.0f, -50.0f),

        Scryver::Math::Vector3Df(-50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f, -50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f, -50.0f),
        Scryver::Math::Vector3Df(-50.0f, -50.0f,  50.0f),
        Scryver::Math::Vector3Df( 50.0f, -50.0f,  50.0f)
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
    Scryver::OpenGL::uniform_t skyCameraLoc = skyBoxShader.getUniform("camera");

    bool depthTest = true;

    while (window.isOpen())
    {
        float dt = gameClock.newFrame();
        count += dt;
        // float scale = 0.5f * sinf(count * 1.0f) + 0.5f;
        // transform.scale(scale, scale, scale);
        transform.worldPos(5.0f * sinf(count * 1.0f), 0, 5.0f * cosf(count * 1.0f));
        transform.rotate(count * 50.0f, count * 50.0f, count * 50.0f);

        if (window.pollEvents())
            break;

        if (window.isKeyPressed(Scryver::Keys::Number_1))
            glManager.wireMode(!glManager.wireMode());

        if (window.isKeyPressed(Scryver::Keys::M))
        {
            if (window.cursorMode() == Scryver::Engine::CursorMode::Normal)
                window.cursorMode(Scryver::Engine::CursorMode::Hidden);
            else if (window.cursorMode() == Scryver::Engine::CursorMode::Hidden)
                window.cursorMode(Scryver::Engine::CursorMode::Centered);
            else if (window.cursorMode() == Scryver::Engine::CursorMode::Centered)
                window.cursorMode(Scryver::Engine::CursorMode::Normal);
        }

        if (window.isKeyPressed(Scryver::Keys::N))
        {
            if (depthTest)
                glManager.disable(Scryver::OpenGL::Option::DepthTest);
            else
                glManager.enable(Scryver::OpenGL::Option::DepthTest);
            depthTest = !depthTest;
        }

        if (window.isKeyDown(Scryver::Keys::W))
            camera.position(camera.position() + camera.target() * dt);
        if (window.isKeyDown(Scryver::Keys::S))
            camera.position(camera.position() - camera.target() * dt);

        if (window.isKeyDown(Scryver::Keys::A))
            camera.position(camera.position() + camera.target().cross(camera.up()).normalized() * dt);
        if (window.isKeyDown(Scryver::Keys::D))
            camera.position(camera.position() - camera.target().cross(camera.up()).normalized() * dt);

        if (window.cursorMode() == Scryver::Engine::CursorMode::Centered)
        {
            Scryver::Math::Vector2Df mouse = window.mousePosition();
            camera.target(camera.target().rotated(mouse.x * 0.05f, camera.up()));
            camera.target(camera.target().rotated(-mouse.y * 0.05f, camera.target().cross(camera.up())));
        }
        else
        {
            if (window.isKeyDown(Scryver::Keys::Q))
                camera.target(camera.target().rotated(-50.0 * dt, camera.up()));
            if (window.isKeyDown(Scryver::Keys::E))
                camera.target(camera.target().rotated(50.0 * dt, camera.up()));
            if (window.isKeyDown(Scryver::Keys::R))
                camera.target(camera.target().rotated(50.0 * dt, camera.target().cross(camera.up())));
            if (window.isKeyDown(Scryver::Keys::F))
                camera.target(camera.target().rotated(-50.0 * dt, camera.target().cross(camera.up())));
        }
        // if (window.isKeyPressed(Scryver::Keys::Number_1))
        //     debugPrint("Keyboard: Number 1");
        // if (window.isKeyPressed(Scryver::Keys::Space))
        //     debugPrint("Keyboard: Space");
        if (window.isKeyPressed(Scryver::Keys::Escape))
        {
            window.close();
            break;
        }

        camera.screenSize(window.size().x, window.size().y);
        glManager.viewport(window.size().x, window.size().y);

        window.clear();

        skyBoxShader.use();
        glUniformMatrix4fv(skyCameraLoc, 1, GL_TRUE, &camera.getViewProjection().m[0][0]);
        glActiveTexture(GL_TEXTURE0);
        glManager.bindSkyBox(skyBox);
        glManager.bindVertexArray(skyBoxVAO);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDisableVertexAttribArray(0);
        glManager.unbindVertexArray();

        shader.use();
        glUniformMatrix4fv(cameraLoc, 1, GL_TRUE, &camera.getWorldViewProjection().m[0][0]);
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
            debugPrint("Camera(" << camera.position().x << ", " << camera.position().y << ", " << camera.position().z << ")");
        }
    }

    shader.destroy();
    glManager.destroy();
    window.destroy();

    return 0;
}
