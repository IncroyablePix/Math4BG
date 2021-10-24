//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_FILETREE_H
#define MATH4BG_FILETREE_H

#include "../IGuiElement.h"

namespace Math4BG
{
    class FileTree : public IGuiElement
    {
    public:
        FileTree(const std::string &name);
        ~FileTree();
        void Begin() override;
        void End() override;
        inline const std::string& GetName() override { return m_name; }
        void Show() override;

    private:
        std::string m_name;
    };
}

#endif //MATH4BG_FILETREE_H
