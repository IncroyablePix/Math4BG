//
// Created by Benjam on 12-04-21.
//

#ifndef ARCPOSITION_WORLD_H
#define ARCPOSITION_WORLD_H


#include <memory>
#include <unordered_map>
#include "../View/Renderer/IRenderer.h"
#include "../View/Renderer/2D/Object/Point.h"
#include "../View/Renderer/2D/Object/Object2D.h"
#include "../View/Renderer/2D/Object/Circle.h"
#include "../View/Renderer/2D/Object/Line.h"
#include "../View/Renderer/2D/Object/SinglePixel.h"
#include "../View/Renderer/2D/Object/Rectangle.h"
#include "../View/Window.h"
#include "../View/Renderer/3D/Shaders/Shader.h"

#define INVALID_OBJECT_ID               (-1)

namespace Math4BG
{
    class World
    {
    public:
        World(const WindowInfo &info, WorldType type, std::shared_ptr<IRenderer> renderer);

        ~World();

        void Draw(Window &window);
        void Update(double lag);

        std::string CreateShader(const std::string& path);

        int CreateCircle(Point center, double radius, uint32_t color);
        bool SetCirclePos(int circleid, Point center);
        bool SetCircleSize(int circleid, double radius);
        bool SetCircleColor(int circleid, uint32_t color);

        int CreateLine(Point start, Point end, uint32_t color);
        bool SetLinePos(int lineid, Point start, Point end);
        bool SetLineColor(int lineid, uint32_t color);

        int CreateDot(Point position, uint32_t color);
        bool SetDotPos(int dotid, Point position);
        bool SetDotColor(int dotid, uint32_t color);

        int CreateRectangle(Point position, int width, int height, uint32_t color);
        bool SetRectanglePos(int rectangleid, Point position);
        bool SetRectangleDimens(int rectangleid, int width, int height);
        bool SetRectangleColor(int rectangleid, uint32_t color);

        void SetBackgroundColor(unsigned int color);

        int CreateCube(const std::string &shaderName);

    private:
        std::unique_ptr<MainCamera> m_camera;
        std::shared_ptr<IRenderer> m_renderer;
        WorldType m_type;

        std::unordered_map<int, std::shared_ptr<IDrawable>> m_objects;
        //std::unordered_map<int, std::shared_ptr<Shader>> m_shaders;
        std::unordered_map<int, Circle> m_circles;
        std::unordered_map<int, Line> m_lines;

        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;

        int m_count = 0;

        template<typename Base, typename T>
        static inline bool instanceof(const T*) {
            return std::is_base_of<Base, T>::value;
        }
    };
}

#endif //ARCPOSITION_WORLD_H
