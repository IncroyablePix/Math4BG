//
// Created by Benjam on 11/30/2021.
//

#ifndef MATH4BG_FILETREECONTENT_H
#define MATH4BG_FILETREECONTENT_H


#include "../IGuiElement.h"
#include "../../../../Transformers/Project/ProjectPackage.h"

namespace Math4BG
{
    class FileTreeContent : public IGuiElement
    {
    public:
        FileTreeContent() = default;
        ~FileTreeContent() = default;
        inline void SetProjectPackage(std::shared_ptr<ProjectPackage> projectPackage) { m_projectPackage = std::move(projectPackage); }
        void Show() override;
        void Begin() override;
        void End() override;
        const std::string & GetName() override;

    private:
        std::shared_ptr<ProjectPackage> m_projectPackage;
        void ShowDirectory(const FileStructure &fileStructure);
    };
}

#endif //MATH4BG_FILETREECONTENT_H
