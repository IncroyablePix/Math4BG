//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_FILETREE_H
#define MATH4BG_FILETREE_H

#include "../IGuiElement.h"
#include "../../../../Transformers/Project/ProjectPackage.h"
#include "FileTreeContent.h"

namespace Math4BG
{
    class FileTree : public IGuiElement
    {
    public:
        explicit FileTree(const std::string &name);
        ~FileTree();
        void Begin() override;
        void End() override;
        inline const std::string& GetName() override { return m_name; }
        void Show() override;
        inline void SetFileTreeContent(std::shared_ptr<FileTreeContent> fileTreeContent) { m_fileTreeContent = std::move(fileTreeContent); }

    private:
        std::string m_name;
        std::shared_ptr<FileTreeContent> m_fileTreeContent;
    };
}

#endif //MATH4BG_FILETREE_H
