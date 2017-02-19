#include "manager.hpp"

#include <GL/glew.h>

#include "Scryver/Debug/Printer.hpp"

using Scryver::OpenGL::GLManager;

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
static void DebugOutputCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
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


GLManager::GLManager()
{

}

GLManager::~GLManager()
{
    destroy();
}

bool GLManager::initialize()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        errorPrint("Failed to initialize GLEW!");
        return false;
    }

    if (GLEW_ARB_debug_output)
    {
        debugPrint("The OpenGL implementation provides debug output. Let's use it !");
        glDebugMessageCallbackARB(&DebugOutputCallback, NULL);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
    }
    else
    {
        debugPrint("ARB_debug_output unavailable. "
                   << "You have to use glGetError() and/or gDebugger to catch mistakes.");
    }

    return true;
}

void GLManager::destroy()
{
    // Empty
}
