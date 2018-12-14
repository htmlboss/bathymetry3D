#include "camera.h"

#include "inputmanager.h"

/***********************************************************************************/
Camera::Camera() noexcept {
    updateVectors();
}

/***********************************************************************************/
void Camera::SetNear(const float near) {
    m_near = near;
}

/***********************************************************************************/
void Camera::SetFar(const float far) {
    m_far = far;
}

/***********************************************************************************/
void Camera::SetSpeed(const float speed) {
    m_speed = speed;
}

/***********************************************************************************/
void Camera::Update(const double deltaTime) {

    if (m_dirty) {
        // Update view from mouse movement
        updateView();

        const auto velocity{ m_speed * static_cast<float>(deltaTime) };

        // Update Keyboard
        if (InputManager::keyPressed(Qt::Key::Key_W)) { m_position += m_front * velocity; }
        if (InputManager::keyPressed(Qt::Key::Key_S)) { m_position -= m_front * velocity; }
        if (InputManager::keyPressed(Qt::Key::Key_A)) { m_position -= m_right * velocity; }
        if (InputManager::keyPressed(Qt::Key::Key_D)) { m_position += m_right * velocity; }
        if (InputManager::keyPressed(Qt::Key::Key_Space)) { m_position += m_worldUp * velocity; }
        if (InputManager::keyPressed(Qt::Key::Key_Control)) { m_position -= m_worldUp * velocity; }
    }
}

/***********************************************************************************/
void Camera::updateView(const bool constrainPitch /*= true*/) {

    const auto xPos{ InputManager::mouseDelta().x() };
    const auto yPos{ InputManager::mouseDelta().y() };

    if (m_firstMouse) {
        m_prevX = xPos;
        m_prevY = yPos;
        m_firstMouse = false;
    }

    const auto xOffset = (xPos - m_prevX) * m_sensitivity;
    const auto yOffset = (m_prevY - yPos) * m_sensitivity; // Reversed since y-coordinates go from bottom to top

    m_prevX = xPos;
    m_prevY = yPos;

    m_yaw += xOffset;
    m_pitch += yOffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (m_pitch > 89.0f) { m_pitch = 89.0f; }
        if (m_pitch < -89.0f) { m_pitch = -89.0f; }
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateVectors();
}

/***********************************************************************************/
void Camera::updateVectors() {
    // Calculate the new Front vector
    glm::vec3 front{
        front.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch)),
        front.y = glm::sin(glm::radians(m_pitch)),
        front.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch))
    };

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_worldUp)); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
