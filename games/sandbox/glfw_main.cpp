#include "config.h"

#include <iostream>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// The ARB_debug_output extension, which is used in this tutorial as an example,
// can call a function of ours with error messages.
// This function must have this precise prototype ( parameters and return value )
// See http://www.opengl.org/registry/specs/ARB/debug_output.txt , "New Types" :
//  The callback function that applications can define, and
//  is accepted by DebugMessageCallbackARB, is defined as:
//
//      typedef void (APIENTRY *DEBUGPROCARB)(enum source,
//                                            enum type,
//                                            uint id,
//                                            enum severity,
//                                            sizei length,
//                                            const char* message,
//                                            void* userParam);
void DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (source == GL_DEBUG_SOURCE_API_ARB && type == GL_DEBUG_TYPE_OTHER_ARB)
    {
        size_t pos = std::string(message).find("will use VIDEO memory as the source for buffer object operati");
        if (pos != std::string::npos)
            return;
    }

    std::cout << "OpenGL Debug Output message : ";

    if(source == GL_DEBUG_SOURCE_API_ARB)                   std::cout << "Source : API; ";
    else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)    std::cout << "Source : WINDOW_SYSTEM; ";
    else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)  std::cout << "Source : SHADER_COMPILER; ";
    else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)      std::cout << "Source : THIRD_PARTY; ";
    else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)      std::cout << "Source : APPLICATION; ";
    else if(source == GL_DEBUG_SOURCE_OTHER_ARB)            std::cout << "Source : OTHER; ";

    if(type == GL_DEBUG_TYPE_ERROR_ARB)                     std::cout << "Type : ERROR; ";
    else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB)  std::cout << "Type : DEPRECATED_BEHAVIOR; ";
    else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB)   std::cout << "Type : UNDEFINED_BEHAVIOR; ";
    else if(type == GL_DEBUG_TYPE_PORTABILITY_ARB)          std::cout << "Type : PORTABILITY; ";
    else if(type == GL_DEBUG_TYPE_PERFORMANCE_ARB)          std::cout << "Type : PERFORMANCE; ";
    else if(type == GL_DEBUG_TYPE_OTHER_ARB)                std::cout << "Type : OTHER; ";

    if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)              std::cout << "Severity : HIGH; ";
    else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)       std::cout << "Severity : MEDIUM; ";
    else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)          std::cout << "Severity : LOW; ";

    // You can set a breakpoint here ! Your debugger will stop the program,
    // and the callstack will immediately show you the offending call.
    std::cout << "Message : " << message << std::endl;
}

int main(int argc, char* argv[]) {
    // Initialise GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_SAMPLES, 4);                                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // create the window
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "GLFW Main", NULL, NULL);
    if( window == NULL ){
        std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    if (GLEW_ARB_debug_output)
    {
        std::cout << "The OpenGL implementation provides debug output. Let's use it !" << std::endl;
        glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    }
    else
    {
        std::cout << "ARB_debug_output unavailable. "
                  << "You have to use glGetError() and/or gDebugger to catch mistakes."
                  << std::endl;
    }

    std::cout << "depth bits:" << glfwGetWindowAttrib(window, GLFW_DEPTH_BITS) << std::endl;
    std::cout << "stencil bits:" << glfwGetWindowAttrib(window, GLFW_STENCIL_BITS) << std::endl;
    std::cout << "antialiasing level:" << glfwGetWindowAttrib(window, GLFW_SAMPLES) << std::endl;
    std::cout << "version:" << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR)
              << "." << glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR) << std::endl;

    bool space, num1, num2, num3, num4, num5, num6;
    // run the main loop
    while (glfwWindowShouldClose(window) == 0)
    {
        // handle events
        glfwPollEvents();
        // To let the thread sleep use:
        // glfwWaitEvents();

        if (!space && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            space = true;
            std::cout << "Keyboard: Space" << std::endl;
        }
        else if (space && glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS)
        {
            space = false;
        }
        if (!num1 && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        {
            num1 = true;
            std::cout << "Keyboard: Num1" << std::endl;
        }
        else if (num1 && glfwGetKey(window, GLFW_KEY_1) != GLFW_PRESS)
        {
            num1 = false;
        }
        if (!num2 && glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        {
            num2 = true;
            std::cout << "Keyboard: Num2" << std::endl;
        }
        else if (num2 && glfwGetKey(window, GLFW_KEY_2) != GLFW_PRESS)
        {
            num2 = false;
        }
        if (!num3 && glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        {
            num3 = true;
            std::cout << "Keyboard: Num3" << std::endl;
        }
        else if (num3 && glfwGetKey(window, GLFW_KEY_3) != GLFW_PRESS)
        {
            num3 = false;
        }
        if (!num4 && glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        {
            num4 = true;
            std::cout << "Keyboard: Num4" << std::endl;
        }
        else if (num4 && glfwGetKey(window, GLFW_KEY_4) != GLFW_PRESS)
        {
            num4 = false;
        }
        if (!num5 && glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        {
            num5 = true;
            std::cout << "Keyboard: Num5" << std::endl;
        }
        else if (num5 && glfwGetKey(window, GLFW_KEY_5) != GLFW_PRESS)
        {
            num5 = false;
        }
        if (!num6 && glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        {
            num6 = true;
            std::cout << "Keyboard: Num6" << std::endl;
        }
        else if (num6 && glfwGetKey(window, GLFW_KEY_6) != GLFW_PRESS)
        {
            num6 = false;
        }
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    return 0;
}
