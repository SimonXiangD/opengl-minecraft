#include "fullScreenOp.h"

void OpenGLWindow::SetFullScreen()
{

    //if (IsFullscreen() == fullscreen)
    //    return;

    if (!fullscreen)
    {
        // backup window position and window size
        glfwGetWindowPos(_wnd, &_wndPos[0], &_wndPos[1]);
        glfwGetWindowSize(_wnd, &_wndSize[0], &_wndSize[1]);

        // get resolution of monitor
        const GLFWvidmode* mode = glfwGetVideoMode(_monitor);

        // switch to full screen
        glfwSetWindowMonitor(_wnd, _monitor, 0, 0, mode->width, mode->height, 0);
    }
    else
    {
        // restore last window size and position
        glfwSetWindowMonitor(_wnd, nullptr, _wndPos[0], _wndPos[1], _wndSize[0], _wndSize[1], 0);
    }
    fullscreen = !fullscreen;
}

OpenGLWindow* OpenGLWindow::Init(GLFWwindow* window)
{
    _wnd = window;
    _monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(_wnd, &_wndSize[0], &_wndSize[1]);
    glfwGetWindowPos(_wnd, &_wndPos[0], &_wndPos[1]);
    fullscreen = false;
    return this;
}