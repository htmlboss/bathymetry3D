#ifndef TRANSFORM3D_H
#define TRANSFORM3D_H

#include <QtGlobal>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

/***********************************************************************************/
class Transform3D {

public:
    Transform3D() = default;

    // Translate
    void translate(const glm::vec3& position);
    void translate(const float dx, const float dy, const float dz);
    void setTranslation(const glm::vec3& position);
    void setTranslation(const float x, const float y, const float z);

    // Scale
    void scale(const glm::vec3& factor);
    void scale(const float dx, const float dy, const float dz);
    void scale(const float factor);
    void setScale(const glm::vec3& scale);
    void setScale(const float x, const float y, const float z);

    // Rotate
    void rotate(const glm::quat& rot);
    void rotate(const float angle, const glm::vec3& axis);
    void rotate(const float angle, const float ax, const float ay, const float az);
    void setRotation(const glm::quat& rot);
    void setRotation(const float angle, const glm::vec3& axis);
    void setRotation(const float angle, const float ax, const float ay, const float az);

    [[nodiscard]] const auto& translation() const noexcept { return m_translation; }
    [[nodiscard]] const auto& scale() const noexcept { return m_scale; }
    [[nodiscard]] const auto& rotation() const noexcept { return m_rotation; }

    [[nodiscard]] glm::mat4x4 toMatrix();

private:
    bool m_dirty{ true };

    glm::vec3 m_translation{ 0.0f };
    glm::vec3 m_scale{ 1.0f };
    glm::quat m_rotation;
    glm::mat4x4 m_worldMatrix;
};

Q_DECLARE_TYPEINFO(Transform3D, Q_MOVABLE_TYPE);

/***********************************************************************************/
inline void Transform3D::translate(const float dx, const float dy, const float dz) {
    translate({dx, dy, dz});
}

/***********************************************************************************/
inline void Transform3D::setTranslation(const float x, const float y, const float z) {
    setTranslation({x, y, z});
}

/***********************************************************************************/
inline void Transform3D::scale(const float dx, const float dy, const float dz) {
    scale({dx, dy, dz});
}

/***********************************************************************************/
inline void Transform3D::scale(const float factor) {
    scale({factor, factor, factor});
}

/***********************************************************************************/
inline void Transform3D::setScale(const float x, const float y, const float z) {
    setScale({x, y, z});
}


#endif // TRANSFORM3D_H
