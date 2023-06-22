#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Spreadsheets/Table.h"


class Window
{
    protected:
        static const char* DEFAULT_NAME;
        static const int DEFAULT_WIDTH;
        static const int DEFAULT_HEIGHT;
        void ShowFullscreen();
        
        GLFWwindow* window;

        virtual void Render();

    public:
        Window();
        Window(const char* name);
        Window(const char* name, int width, int height);
        virtual void Run();
        ~Window();
};

