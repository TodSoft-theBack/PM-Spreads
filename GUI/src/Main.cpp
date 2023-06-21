#include <GLFW/glfw3.h>
#include <Windows.h>
#include "Window.h"


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (!glfwInit())
        return EXIT_FAILURE;

    Window window("PM Spreads");
    window.Run();

    return EXIT_SUCCESS;
}