#ifndef SCRYVER_OPENGL_MANAGER_HPP
#define SCRYVER_OPENGL_MANAGER_HPP

namespace Scryver {

namespace OpenGL {

class GLManager
{
public:
    GLManager();
    ~GLManager();

    bool initialize();
    void destroy();


};

}  // namespace OpenGL

}  // namespace Scryver

#endif  // SCRYVER_OPENGL_MANAGER_HPP
