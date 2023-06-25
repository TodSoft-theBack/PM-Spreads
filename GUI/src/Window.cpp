#include "Window.h"
#include <Windows.h>
#include <shobjidl.h> 
#include <codecvt>
#include "Spreadsheets/TableFile.h"
#include <sstream>

const char* Window::DEFAULT_NAME = "Basic window";
const int Window::DEFAULT_WIDTH = 1280;
const int Window::DEFAULT_HEIGHT = 720;

ImGuiStyle* BaseStyle();

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
                HRESULT executionCode = CoInitializeEx
                (
                    NULL, 
                    COINIT_APARTMENTTHREADED | 
                    COINIT_DISABLE_OLE1DDE
                );

                if (SUCCEEDED(executionCode))
                {
                    IFileOpenDialog* openFileDialog = nullptr;

                    executionCode = CoCreateInstance
                    (
                        CLSID_FileOpenDialog,
                        NULL, 
                        CLSCTX_ALL, 
                        IID_IFileOpenDialog, 
                        reinterpret_cast<void**>(&openFileDialog)
                    );

                    if (SUCCEEDED(executionCode))
                    {
                        executionCode = openFileDialog->Show(NULL);

                        if (SUCCEEDED(executionCode))
                        {
                            IShellItem* shell = nullptr;
                            executionCode = openFileDialog->GetResult(&shell);

                            if (SUCCEEDED(executionCode))
                            {
                                wchar_t* path;
                                executionCode = shell->GetDisplayName(SIGDN_FILESYSPATH, &path);
                                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
                                fileManager.OpenFile(convert.to_bytes(path).c_str());

                                if (SUCCEEDED(executionCode))
                                    CoTaskMemFree(path);
                                shell->Release();
                            }
                        }
                        openFileDialog->Release();
                    }
                    CoUninitialize();
                }
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
    }

    size_t filesCount = fileManager.Count();
    TableFile* selectedFile = nullptr;
    if (ImGui::BeginTabBar("Files"))
    {
        for (size_t i = 0; i < filesCount; i++)
        {
            File* file = fileManager[i];
            int lastIndex = file->Filename().LastIndexOf('\\');
            String tabText = file->Filename().Substring(lastIndex+1);

            //ImGuiTabItemFlags flags = i != filesCount-1 ? 0 : ImGuiTabItemFlags_SetSelected;

            if (ImGui::BeginTabItem(tabText))
            {
                selectedFile = (TableFile*)file;
                ImGui::EndTabItem();
            }
            

        }
        ImGui::EndTabBar();
    }
    

    try
    {
        if (selectedFile != nullptr)
        {
            
            if (ImGui::BeginTable("TableArea", selectedFile->table.Columns()))
            {
                for (int row = 0; row < selectedFile->table.Rows(); row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < selectedFile->table.Columns(); column++)
                    {
                        String cell = selectedFile->table[row][column]->Evaluate(selectedFile->table.Collection());
                        ImGui::TableSetColumnIndex(column);
                        float cellWidth = ImGui::GetWindowWidth() / selectedFile->table.Columns() - 16;

                        ImGui::Button(cell, ImVec2(cellWidth, 32));

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();;
                            ImGui::Text(selectedFile->table[row][column]->ToString());
                            ImGui::EndTooltip();
                        }
                    }
                }
                ImGui::EndTable();
            }
        }
    }
    catch (const std::runtime_error& ex)
    {
        ImGui::OpenPopup("ExceptionPopUp");
        if (ImGui::BeginPopupModal("ExceptionPopUp", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove))
        {
            ImGui::Text(ex.what());
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
        }
        ImGui::EndPopup();
    }
    catch (...)
    {
        std::cout << "Generic error";
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
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 18.0f);
    ImGui::StyleColorsLight(BaseStyle());
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

ImGuiStyle* BaseStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();

    return style;
}