#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <QPoint>
/***********************************************************************************/
// Forward declarations
class OpenGLWidget;

/***********************************************************************************/
class InputManager {
    friend class OpenGLWidget;
public:

    // Possible key states
    enum InputState {
        InputInvalid = 0,
        InputRegistered,
        InputUnregistered,
        InputTriggered,
        InputPressed,
        InputReleased
    };

    // State checking
    static InputState keyState(const Qt::Key key);
    static bool keyTriggered(const Qt::Key key);
    static bool keyPressed(const Qt::Key key);
    static bool keyReleased(const Qt::Key key);
    static InputState buttonState(const Qt::MouseButton button);
    static bool buttonTriggered(const Qt::MouseButton button);
    static bool buttonPressed(const Qt::MouseButton button);
    static bool buttonReleased(const Qt::MouseButton button);
    static QPoint mousePosition();
    static QPoint mouseDelta();

private:
    // State updating
    static void update();
    static void registerKeyPress(const int key);
    static void registerKeyRelease(const int key);
    static void registerMousePress(const Qt::MouseButton button);
    static void registerMouseRelease(const Qt::MouseButton button);
    static void reset();
};

/***********************************************************************************/
inline bool InputManager::keyTriggered(const Qt::Key key) {
    return keyState(key) == InputState::InputTriggered;
}

/***********************************************************************************/
inline bool InputManager::keyPressed(const Qt::Key key) {
    return keyState(key) == InputState::InputPressed;
}

/***********************************************************************************/
inline bool InputManager::keyReleased(const Qt::Key key) {
    return keyState(key) == InputState::InputReleased;
}

/***********************************************************************************/
inline bool InputManager::buttonTriggered(const Qt::MouseButton button) {
    return buttonState(button) == InputState::InputTriggered;
}

/***********************************************************************************/
inline bool InputManager::buttonPressed(const Qt::MouseButton button) {
    return buttonState(button) == InputState::InputPressed;
}

/***********************************************************************************/
inline bool InputManager::buttonReleased(const Qt::MouseButton button) {
    return buttonState(button) == InputState::InputReleased;
}

#endif // INPUTMANAGER_H
