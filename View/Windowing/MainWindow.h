//
// Created by Benjam on 10/15/2021.
//

#ifndef MATH4BG_MAINWINDOW_H
#define MATH4BG_MAINWINDOW_H

#include <SDL2/SDL.h>
#include "../IWindow.h"
#include "../IMGUI/imgui.h"
#include "../../Transformers/Contexts.h"
#include "../../Output/IOutput.h"
#include "../IMGUI/Own/CodeEditor.h"
#include "../IMGUI/ImGuiFileBrowser.h"
#include "../IMGUI/Own/Docking/MainDockSpace.h"
#include "../IMGUI/Own/Main/EditorView.h"

namespace Math4BG
{
    class MainWindow : public IWindow
    {
    public:
        explicit MainWindow(const WindowInfo &info, std::shared_ptr<IOutput> output);
        ~MainWindow();
        void SetMouseProps(const ImVec2& position, const int buttons, const int wheel);
        void Update(double lag);
        void Render(double delta) const;
        void Resize(int width, int height) override;

        void SetContexts(std::shared_ptr<Contexts> contexts);
        void SetCodeEditor(std::shared_ptr<CodeEditor> codeEditor);

    protected:
        void UpdateWindowTitle() override;

    private:
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
        SDL_GLContext m_glContext;

        static uint32_t FlagsFor();
        static void InitSDL();
        void InitImGui();

        void GlewInitAttempt();

        std::shared_ptr<IOutput> m_output;

        std::unique_ptr<imgui_addons::ImGuiFileBrowser> m_fileDialog;

        std::unique_ptr<MainDockSpace> m_dockSpace;
        std::shared_ptr<EditorView> m_editorView;
    };

    static bool sdl2Initialized = false;
    static bool glew3Initialized = false;
}

#endif //MATH4BG_MAINWINDOW_H
