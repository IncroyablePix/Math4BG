//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_WORLD_H
#define ARCPOSITION_WORLD_H


#include <memory>
#include <unordered_map>
#include "../View/Renderer/OG33RendererSDL.h"
#include "../View/Renderer/OG33Renderer.h"
#include "../View/Renderer/2D/Object/Point.h"
#include "../View/Renderer/2D/Object/Object2D.h"
#include "../View/Renderer/2D/Object/Circle.h"
#include "../View/Renderer/2D/Object/Line.h"
#include "../View/Renderer/2D/Object/Rectangle.h"
#include "../View/Window.h"
#include "../View/Renderer/3D/Shaders/Shader.h"
#include "../Physics/Transform.h"
#include "../IO/ModelData.h"
#include "../View/Renderer/3D/Texture/Texture.h"
#include "../View/Renderer/3D/Light/Light.h"
#include "../View/Renderer/3D/Light/DirectionalLight.h"
#include "../View/Renderer/3D/PostProcessing/ViewportSquare.h"
#include "../View/Renderer/3D/Texture/FrameBuffer/FrameBufferObject.h"

#define INVALID_OBJECT_ID               (-1)

namespace Math4BG
{
    class World
    {
    public:
        World(const WindowInfo &info, std::shared_ptr<OG33Renderer> renderer);

        ~World();

        void Draw(const std::string& title);
        void DrawWorld();
        void Update(double lag);//, const MouseInput &mouse, const KeyInput &keys);

        //std::string CreateShader(const std::string& path);

        void SetCameraPos(const glm::vec3 &pos);
        void SetCameraRot(const glm::vec2 &pos);

        void SetBackgroundColor(unsigned int color);

        int CreateCube(std::shared_ptr<Shader> shader, Transform& transform);
        int CreatePlane(std::shared_ptr<Shader> shader, Transform& transform);
        int CreatePyramid(std::shared_ptr<Shader> shader, Transform &transform);
        int CreateCustomObject(ModelData* model, std::shared_ptr<Shader> shader, Transform& transform);

        bool SetObjectColor(int objid, const glm::vec4 &color);
        bool SetObjectPos(int objid, const glm::vec3 &position);
        bool SetObjectPosOrigin(int objid, const glm::vec3 &position);
        bool SetObjectOrigin(int objid, const glm::vec3 &position);
        bool SetObjectRot(int objid, const glm::vec3 &rot);
        bool SetObjectScale(int objid, const glm::vec3 &scale);
        bool SetObjectTexture(int obj, std::shared_ptr<Texture> texture);
        bool SetObjectColor(int objid, const glm::vec3 &color);

        int CreatePointLight(float intensity, const glm::vec3 &color, const Transform& transform);
        bool SetLightPos(int lightid, const glm::vec3 &position);
        bool SetLightColor(int lightid, const glm::vec3 &color);

        bool SetDirectionalLight(float intensity, const glm::vec3 &orientation, const glm::vec3 &color);

        void Resize(int width, int height);
        inline unsigned int GetFboId() const { return m_fbo.GetId(); }
        inline std::shared_ptr<Texture> GetFboTexture() const { return m_fbo.GetTexture(); }

        void UpdateShaders(std::unordered_map<std::string, std::shared_ptr<Shader>>& shaders);

        void HandleMouseInputs();
        void HandleKeyboardInputs();

        inline void SetWindowActive(bool active) { m_windowActive = active; }

    private:
        std::unique_ptr<MainCamera> m_camera;
        std::shared_ptr<OG33Renderer> m_renderer;

        std::shared_ptr<Shader> m_ppShader = Shader::CreateShader(ParseShader("shaders/background.shader"));
        ViewportSquare m_canvas;
        FrameBufferObject m_fbo;

        DirectionalLight m_directionalLight;
        std::unordered_map<int, std::shared_ptr<Light>> m_lights;
        std::unordered_map<int, std::shared_ptr<IDrawable>> m_objects;

        MouseInput m_mouse;
        KeyInput m_keys;

        bool m_windowActive;
        bool m_tabActive;

        int m_count = 0;

        template<typename Base, typename T>
        static inline bool instanceof(const T*) {
            return std::is_base_of<Base, T>::value;
        }
    };
}

#endif //ARCPOSITION_WORLD_H
