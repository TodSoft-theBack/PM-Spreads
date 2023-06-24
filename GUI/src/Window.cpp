#include "Window.h"
#include "Spreadsheets/TableFile.h"

const char* Window::DEFAULT_NAME = "Basic window";
const int Window::DEFAULT_WIDTH = 1280;
const int Window::DEFAULT_HEIGHT = 720;

void Window::ShowFullscreen()
{
    static bool isOpen = true;
    static bool use_work_area = true;
    static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);
    if (ImGui::Begin("Example: Fullscreen window", &isOpen, flags))
    {
        ImGui::BeginMainMenuBar();

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open file", "Ctrl+O"))
            {

            }

            if (ImGui::MenuItem("Save current", "Ctrl+S"))
            {

            }

            if (ImGui::MenuItem("Save as", "Ctrl+Shift+S"))
            {

            }

            if (ImGui::MenuItem("Close", "Ctrl+W"))
                isOpen = false;
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();


        Table Table(5,5);
        try
        {
            TableFile tableFile("D:\\Coding\\PM Spreads\\Spreadsheets\\Pepe.csv");
            Table = tableFile.table;
            if (ImGui::BeginTable("Example.csv", Table.Columns()))
            {
                for (int row = 0; row < Table.Rows(); row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < Table.Columns(); column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        ImGui::Text(Table[row][column]->Evaluate(Table.Collection()));
                    }
                }
                ImGui::EndTable();
            }
        }
        catch (const std::runtime_error& ex)
        {
            ImGui::Text(ex.what());
        }
        catch (...)
        {
            std::cout << "Generic error";
        }
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
    uint8_t* pixels = nullptr;
    GLFWimage image[1];
    image[0].height = 20;
    image[0].width = 20;
    image[0].pixels = pixels;
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
    ImGui::StyleColorsDark();
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