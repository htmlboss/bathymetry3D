#include "transform3d.h"


/***********************************************************************************/
void Transform3D::translate(const glm::vec3& position) {
    m_dirty = true;
    m_translation += position;
}

/***********************************************************************************/
void Transform3D::setTranslation(const glm::vec3& position) {
    m_dirty = true;
    m_translation = position;
}

/***********************************************************************************/
void Transform3D::scale(const glm::vec3& factor) {
    m_dirty = true;
    m_scale *= factor;
}

/***********************************************************************************/
void Transform3D::setScale(const glm::vec3& scale) {
    m_dirty = true;
    m_scale = scale;
}

/***********************************************************************************/
void Transform3D::rotate(const glm::quat& rot) {
    m_dirty = true;
    m_rotation *= rot;
}

/***********************************************************************************/
void Transform3D::setRotation(const glm::quat& rot) {
    m_dirty = true;
    m_rotation = rot;
}

/***********************************************************************************/
glm::mat4x4 Transform3D::toMatrix() {
    if (m_dirty) {
        m_dirty = false;

        auto newWorldMat{ glm::translate(glm::mat4x4(1.0f), m_translation) };
        //ADD ROTATE
        newWorldMat = glm::scale(newWorldMat, m_scale);

        m_worldMatrix = newWorldMat;
    }

    return m_worldMatrix;
}
