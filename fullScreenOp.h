#ifndef FULLSCREENOP_H_
#define FULLSCREENOP_H_
#include <GLFW/glfw3.h>
#include <array>
#include <stdexcept>

class OpenGLWindow
{
private:

    std::array< int, 2 > _wndPos{ 0, 0 };
    std::array< int, 2 > _wndSize{ 0, 0 };
    std::array< int, 2 > _vpSize{ 0, 0 };
    GLFWwindow* _wnd = nullptr;
    GLFWmonitor* _monitor = nullptr;
    bool fullscreen = false;


public:

    OpenGLWindow* Init(GLFWwindow* window);
    bool IsFullscreen(void);
    void SetFullScreen();
};



inline bool OpenGLWindow::IsFullscreen(void)
{
    return glfwGetWindowMonitor(_wnd) != nullptr;
}



#endif