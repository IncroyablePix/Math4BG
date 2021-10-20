//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_DOCKSPACE_H
#define MATH4BG_DOCKSPACE_H

#include <string>
#include <array>
#include <memory>
#include <unordered_map>
#include "../IGuiElement.h"
#include "../../imgui.h"
#include "../../imgui_internal.h"

namespace Math4BG
{
    enum DockSlot
    {
        DOCK_CENTER = ImGuiDir_COUNT,
        DOCK_TOP = ImGuiDir_Up,
        DOCK_BOTTOM = ImGuiDir_Down,
        DOCK_LEFT = ImGuiDir_Left,
        DOCK_RIGHT = ImGuiDir_Right
    };

    class DockSpace : public IGuiElement
    {
    public:
        explicit DockSpace(const std::string &title, ImGuiID dockspaceId);
        ~DockSpace();
        void Show() override;
        inline const std::string & GetName() override { return m_title; }
        void AddElement(std::shared_ptr<IGuiElement> element, DockSlot slot);

    protected:
        bool m_firstTime { true };
        ImGuiID m_dockspaceId;
        std::string m_title;
        std::unordered_map<DockSlot, std::shared_ptr<IGuiElement>> m_elements;

        void ShowElements(ImGuiID dockspaceId);
    };
}

#endif //MATH4BG_DOCKSPACE_H
