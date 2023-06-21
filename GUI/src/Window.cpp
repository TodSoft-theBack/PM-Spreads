#include "Window.h"

const char* Window::DEFAULT_NAME = "Basic window";
const int Window::DEFAULT_WIDTH = 1280;
const int Window::DEFAULT_HEIGHT = 720;

void Window::ShowFullscreen()
{
    static bool isOpen = true;
    static bool use_work_area = true;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
    // Based on your use case you may want one or the other.
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    if (ImGui::Begin("Example: Fullscreen window", &isOpen , flags))
    {
        //TO DO: Render Table Here ....
    }
    ImGui::End();
}

void Window::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ShowFullscreen();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Window::Window() : Window(DEFAULT_NAME) { }

Window::Window(const char* name) : Window(name, DEFAULT_WIDTH, DEFAULT_HEIGHT) {}

Window::Window(const char* name, int width, int height)
{
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Could not create window!!!");
    }
    glfwMakeContextCurrent(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void Window::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}