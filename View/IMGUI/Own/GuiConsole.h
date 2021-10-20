//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_GUICONSOLE_H
#define MATH4BG_GUICONSOLE_H

#include <string>
#include <memory>
#include "IGuiElement.h"
#include "../../../Output/IOutput.h"

namespace Math4BG
{
    class GuiConsole : public IGuiElement
    {
    public:
        GuiConsole(const std::string &name, std::shared_ptr<IOutput> output);
        ~GuiConsole() = default;
        void Show() override;
        inline const std::string& GetName() override { return m_name; };

    private:
        std::shared_ptr<IOutput> m_output;
        std::string m_name;
    };
}

#endif //MATH4BG_GUICONSOLE_H
