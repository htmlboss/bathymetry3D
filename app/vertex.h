#ifndef VERTEX_H
#define VERTEX_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct [[nodiscard]] Vertex_Pos {
    glm::vec3 Position;
};

struct [[nodiscard]] Vertex_PosColor {
    glm::vec3 Position;
    glm::vec3 Color;
};

struct [[nodiscard]] Vertex_PosNormalUV {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
};

#endif // VERTEX_H
