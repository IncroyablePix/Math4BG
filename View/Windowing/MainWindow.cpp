//
// Created by Benjam on 10/15/2021.
//

#include <sstream>
#include <GL/glew.h>
#include <iostream>
#include <utility>
#include "MainWindow.h"
#include "../IMGUI/imgui_impl_opengl3.h"
#include "../IMGUI/imgui_impl_sdl.h"
#include "../IMGUI/imgui_internal.h"
#include "../../Output/ImGuiConsole/ImGuiOutput.h"
#include "../IMGUI/Own/CodeEditor.h"
#include "../IMGUI/Own/GuiConsole.h"
#include "../IMGUI/Own/FileTree/FileTree.h"

namespace Math4BG
{
    MainWindow::MainWindow(const WindowInfo &info, std::shared_ptr<IOutput> output) :
    IWindow(info),
    m_window(nullptr, SDL_DestroyWindow),
    m_output(std::move(output)),
    m_fileDialog(std::make_unique<imgui_addons::ImGuiFileBrowser>()),
    m_dockSpace(std::make_unique<MainDockSpace>("MainDockWindow", 0)),
    m_editorView(std::make_shared<EditorView>("Code editor"))
    {
        InitSDL();

        m_window.reset(SDL_CreateWindow(info.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info.width,
                                        info.height, FlagsFor()));

        if (!m_window)
            throw std::runtime_error("La fenêtre n'a pas pu être créée !");

        m_glContext = SDL_GL_CreateContext(m_window.get());
        SDL_GL_MakeCurrent(m_window.get(), m_glContext);
        GlewInitAttempt();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glCullFace(GL_BACK);

        glViewport(0, 0, info.width, info.height);

        InitImGui();

        //--- GuiElements
        auto mainDock = std::make_shared<DockSpace>("MainDock", 1);
        //mainDock->AddElement(m_editorView, DOCK_TOP);
        //mainDock->AddElement(std::make_shared<GuiConsole>("Console", m_output), DOCK_RIGHT);
        m_dockSpace->AddElement(m_editorView, DOCK_TOP);
        m_dockSpace->AddElement(std::make_shared<GuiConsole>("Console", m_output), DOCK_BOTTOM);
        //m_dockSpace->AddElement(mainDock, DOCK_CENTER);
        m_dockSpace->AddElement(std::make_shared<FileTree>("Files"), DOCK_LEFT);
        //m_dockSpace->AddElement()
    }

    MainWindow::~MainWindow()
    {
        //ImGui_ImplOpenGL3_Shutdown();
        //ImGui_ImplSDL2_Shutdown();
        //ImGui::DestroyContext();
        SDL_GL_DeleteContext(m_glContext);
    }

    void MainWindow::UpdateWindowTitle()
    {
        std::ostringstream ss;
        ss << m_title << " (" << m_fps << "FPS - " << m_ups << "UPS)";
        SDL_SetWindowTitle(m_window.get(), ss.str().c_str());
    }

    uint32_t MainWindow::FlagsFor()
    {
        return SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
    }

    void MainWindow::InitSDL()
    {
        if(!sdl2Initialized)
        {
            if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO))
                throw std::runtime_error(SDL_GetError());

            SDL_version compiled;
            SDL_VERSION(&compiled);

            std::ostringstream compiledVal;
            compiledVal << "Compiled with "
                        << std::to_string(compiled.major)
                        << "." << std::to_string(compiled.minor)
                        << "." << std::to_string(compiled.patch);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
            sdl2Initialized = true;
        }
    }

    void MainWindow::Render(double delta) const
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGuiIO& io = ImGui::GetIO();


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        //--- Main Menu
        bool open = false;
        if(ImGui::BeginMainMenuBar())
        {
            if(ImGui::BeginMenu("File"))
            {
                if(ImGui::MenuItem("Open...", nullptr))
                {
                    open = true;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if(open)
            ImGui::OpenPopup("Open File");

        if(m_fileDialog->showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".rar,.zip,.7z"))
        {
            std::cout << m_fileDialog->selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << m_fileDialog->selected_path << std::endl;    // The absolute path to the selected file
        }
        //--- Dock Space
        /*ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGuiID mainDockSpaceId = 0;

        // Central dockspace should take up all space
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar |
                                       ImGuiWindowFlags_NoDocking |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::Begin("MainDockSpace", nullptr, windowFlags);

        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) // If docking enabled
        {
            ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

            static bool firstTime = true;
            if (firstTime)
            {
                firstTime = false;

                ImGui::DockBuilderRemoveNode(mainDockSpaceId); // clear any previous layout
                ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

                // split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the following args in the following order
                //   window ID to split, direction, fraction (between 0 and 1), the final two setting let's us choose which id we want (which ever one we DON'T set as NULL, will be returned by the function)
                //                                                              out_id_at_dir is the id of the node in the direction we specified earlier, out_id_at_opposite_dir is in the opposite direction
                auto dockFiles = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.2f, nullptr, &dockspaceId);
                auto dockMain = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Up, 0.75f, nullptr, &dockspaceId);
                auto dockConsole = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Down, 0.25f, nullptr, &dockspaceId);

                // we now dock our windows into the docking node we made above
                ImGui::DockBuilderDockWindow("Console", dockConsole);
                ImGui::DockBuilderDockWindow("Files", dockFiles);
                ImGui::DockBuilderDockWindow("Main", dockMain);
                ImGui::DockBuilderFinish(dockspaceId);
            }
        }

        ImGui::End();*/

        //ImGui::DockSpace(mainDockSpaceId, ImVec2(), ImGuiDockNodeFlags_PassthruCentralNode);

        /*static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", nullptr, windowFlags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);

            static auto first_time = true;
            if (first_time)
            {
                first_time = false;

                ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
                ImGui::DockBuilderAddNode(dockspace_id, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

                // split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the following args in the following order
                //   window ID to split, direction, fraction (between 0 and 1), the final two setting let's us choose which id we want (which ever one we DON'T set as NULL, will be returned by the function)
                //                                                              out_id_at_dir is the id of the node in the direction we specified earlier, out_id_at_opposite_dir is in the opposite direction
                auto dockFiles = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
                auto dockMain = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 0.75f, nullptr, &dockspace_id);
                auto dockConsole = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);

                // we now dock our windows into the docking node we made above
                ImGui::DockBuilderDockWindow("Console", dockConsole);
                ImGui::DockBuilderDockWindow("Files", dockFiles);
                ImGui::DockBuilderDockWindow("Main", dockMain);
                ImGui::DockBuilderFinish(dockspace_id);
            }
        }

        ImGui::End();*/
        //ImGui::Add
        /*ImGuiDock::Dockspace dockspace;
        ImGuiDock::Dock mainDock;
        ImGuiDock::Dock leftDock;*/

        /*ImGui::Begin("Files");
        ImGui::Text("Files!");
        ImGui::End();


        m_output->Show();

        ImGui::Begin("Console");
            auto output = m_output.get();
            output->PrintMessages();ImGui::End();

            ImGui::Begin("Main");
            ImGui::BeginTabBar("Windows");
            if(ImGui::BeginTabItem("Code"))
            {
                if(m_codeEditor)
                    m_codeEditor->Show();
                else
                    ImGui::Text("Hello, top!");

                ImGui::EndTabItem();
            }
            m_contexts->DrawContexts();
            ImGui::EndTabBar();
        ImGui::End();*/

        m_dockSpace->Show();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(m_window.get());
    }

    void MainWindow::Update(double lag)
    {
        ImGui::GetIO().DeltaTime = lag;
    }

    void MainWindow::Resize(int width, int height)
    {
        m_width = width;
        m_height = height;

        ImGuiIO& imGuiIo = ImGui::GetIO();
        imGuiIo.DisplaySize.x = static_cast<float>(width);
        imGuiIo.DisplaySize.y = static_cast<float>(height);
    }

    void MainWindow::SetMouseProps(const ImVec2 &position, const int buttons, const int wheel)
    {
        ImGuiIO& imGuiIo = ImGui::GetIO();
        imGuiIo.MousePos = position;
        imGuiIo.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        imGuiIo.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
        imGuiIo.MouseWheel = static_cast<float>(wheel);
    }

    void MainWindow::GlewInitAttempt()
    {
        if(!glew3Initialized)
        {
            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK)
                throw std::runtime_error("Failed to initialize GLEW.");

            /*printf("----------------------------------------------------------------\n");
            printf("Graphics Successfully Initialized\n");
            printf("OpenGL Info\n");
            printf("    Version: %s\n", glGetString(GL_VERSION));
            printf("     Vendor: %s\n", glGetString(GL_VENDOR));
            printf("   Renderer: %s\n", glGetString(GL_RENDERER));
            printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
            printf("----------------------------------------------------------------\n");*/

            glew3Initialized = true;
        }
    }

    void MainWindow::InitImGui()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& imGuiIo = ImGui::GetIO(); (void) imGuiIo;
        imGuiIo.DisplaySize.x = static_cast<float>(m_width);
        imGuiIo.DisplaySize.y = static_cast<float>(m_height);
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //imGuiIo.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(m_window.get(), m_glContext);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void MainWindow::SetContexts(std::shared_ptr<Contexts> contexts)
    {
        m_editorView->SetContexts(contexts);
        //m_contexts = std::move(contexts);
    }

    void MainWindow::SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor)
    {
        m_editorView->SetCodeEditor(codeEditor);
        //m_codeEditor = std::move(codeEditor);
    }
}