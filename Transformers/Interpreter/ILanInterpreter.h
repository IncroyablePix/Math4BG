//
// Created by Benjam on 19-05-21.
//

#ifndef MATH4BG_ILANINTERPRETER_H
#define MATH4BG_ILANINTERPRETER_H

#include <string>
#include <memory>
#include "../Contexts.h"
#include "../../Output/IOutput.h"

#define LANGUAGE_LUA            "lua"
#define LANGUAGE_JS             "js"

namespace Math4BG
{
    class ILanInterpreter : std::enable_shared_from_this<ILanInterpreter>
    {
    public:
        ILanInterpreter(std::shared_ptr<Contexts> contexts, std::shared_ptr<IOutput> output);
        virtual ~ILanInterpreter() = default;

        virtual void ExecuteFile(const std::string &path) = 0;

        virtual int CallOnInitFunction() = 0;
        virtual int CallUpdateFunction(double lag) = 0;

        virtual void RegisterFunctions() = 0;

        //--- Added functions
        void PrintImplementation(const std::string &message);

        int CreateContextImplementation(const std::string &title, unsigned int width, unsigned int height, bool abstract);

        void SetCameraPosImplementation(int contextid, float x, float y, float z);
        void SetCameraRotImplementation(int contextid, float x, float y);

        std::string CreateShaderImplementation(const std::string &path);
        bool CreateTextureImplementation(const std::string &path, const std::string &name);
        bool CreateModelImplementation(const std::string &path, const std::string &name);

        long long int GetMillisImplementation();

        void SetBackgroundColorImplementation(int contextid, unsigned int color);

        int CreateCubeImplementation(int contextid, const std::string &shaderName, float x, float y, float z);
        int CreatePlaneImplementation(int contextid, const std::string &shaderName, float x, float y, float z);
        int CreatePyramidImplementation(int contextid, const std::string &shaderName, float x, float y, float z);
        int CreateCustomObjectImplementation(int contextid, const std::string &shaderName, const std::string &modelName, float x, float y, float z);

        bool SetObjectPosImplementation(int id, float x, float y, float z);
        bool SetObjectRotImplementation(int id, float x, float y, float z);
        bool SetObjectScaleImplementation(int id, float x, float y, float z);
        bool SetObjectPosOriginImplementation(int id, float x, float y, float z);
        bool SetObjectOriginImplementation(int id, float x, float y, float z);
        bool SetObjectColorImplementation(int id, unsigned int color);
        bool SetObjectTextureImplementation(int id, const std::string &name);

        bool SetDirectionalLightImplementation(int contextid, float x, float y, float z, float intensity, unsigned int color);

        int CreatePointLightImplementation(int contextid, float intensity, unsigned int color, float x, float y, float z);
        bool SetLightPosImplementation(int id, float x, float y, float z);
        bool SetLightColorImplementation(int id, unsigned int color);

    protected:
        std::shared_ptr<IOutput> m_output;
        std::shared_ptr<Contexts> m_contexts;
    };
}

#endif //MATH4BG_ILANINTERPRETER_H
