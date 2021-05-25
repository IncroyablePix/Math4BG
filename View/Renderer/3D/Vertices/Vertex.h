//
// Created by Benjam on 20-05-21.
//

#ifndef MATH4BG_VERTEX_H
#define MATH4BG_VERTEX_H


#include <glm/glm.hpp>

struct Vertex
{
    Vertex() = default;
    Vertex(glm::vec3 position, glm::vec3 col, glm::vec2 uvs, glm::vec3 normal) : position(position), col(col), uvs(uvs), normal(normal) { }

    glm::vec3 position;
    glm::vec3 col;
    glm::vec2 uvs;
    glm::vec3 normal;
};


#endif //MATH4BG_VERTEX_H
