#include "inputmanager.h"

#include <utility>
#include <vector>

#include <QCursor>

/***********************************************************************************/
template <typename T>
struct InputInstance : std::pair<T, InputManager::InputState> {

    using base_class = std::pair<T, InputManager::InputState>;

    inline InputInstance(const T value) : base_class{value, InputManager::InputInvalid} {}
    inline InputInstance(const T value, InputManager::InputState state) : base_class{value, state} {}

    inline auto operator==(const InputInstance& rhs) const noexcept {
        return this->first == rhs.first;
    }
};

/***********************************************************************************/
// Instance types
using KeyInstance = InputInstance<Qt::Key>;
using ButtonInstance = InputInstance<Qt::MouseButton>;

// Container types
using KeyContainer = std::vector<KeyInstance>;
using ButtonContainer = std::vector<ButtonInstance>;

// Globals
static KeyContainer sg_keyInstances;
static ButtonContainer sg_buttonInstances;
static QPoint sg_mouseCurrPosition;
static QPoint sg_mousePrevPosition;
static QPoint sg_mouseDelta;

/***********************************************************************************/
static inline auto FindKey(const Qt::Key value) {
    return std::find(sg_keyInstances.begin(), sg_keyInstances.end(), value);
}

/***********************************************************************************/
static inline auto FindButton(const Qt::MouseButton value) {
    return std::find(sg_buttonInstances.begin(), sg_buttonInstances.end(), value);
}

/***********************************************************************************/
template <typename TPair>
static inline void UpdateStates(TPair& instance) {

    switch (instance.second) {
    case InputManager::InputRegistered:
        instance.second = InputManager::InputTriggered;
        break;
    case InputManager::InputTriggered:
        instance.second = InputManager::InputPressed;
        break;
    case InputManager::InputUnregistered:
        instance.second = InputManager::InputReleased;
        break;
    default:
        break;
    }
}

/***********************************************************************************/
template <typename TPair>
static inline constexpr bool CheckReleased(const TPair& instance) noexcept {
    return instance.second == InputManager::InputReleased;
}

/***********************************************************************************/
template <typename Container>
static inline void Update(Container& container) {

    using TPair = typename Container::value_type;

    // Remove old data
    const auto& remove{ std::remove_if(container.begin(), container.end(), std::addressof(CheckReleased<TPair>)) };
    container.erase(remove, container.end());

    // Update existing data
    std::for_each(container.begin(), container.end(), std::addressof(UpdateStates<TPair>));
}

/***********************************************************************************/
InputManager::InputState InputManager::keyState(const Qt::Key k) {
    const auto& it{ FindKey(k) };

    return (it != sg_keyInstances.end()) ? it->second : InputInvalid;
}

/***********************************************************************************/
InputManager::InputState InputManager::buttonState(const Qt::MouseButton k) {
    const auto& it{ FindButton(k) };

    return (it != sg_buttonInstances.end()) ? it->second : InputInvalid;
}

/***********************************************************************************/
QPoint InputManager::mousePosition() {
    return QCursor::pos();
}

/***********************************************************************************/
QPoint InputManager::mouseDelta() {
    return sg_mouseDelta;
}

/***********************************************************************************/
void InputManager::update() {
    // Update Mouse Delta
    sg_mousePrevPosition = sg_mouseCurrPosition;
    sg_mouseCurrPosition = QCursor::pos();
    sg_mouseDelta = sg_mouseCurrPosition - sg_mousePrevPosition;

    // Update KeyState values
    Update(sg_buttonInstances);
    Update(sg_keyInstances);
}

/***********************************************************************************/
void InputManager::registerKeyPress(const int k) {

    if (auto it{FindKey(static_cast<Qt::Key>(k))}; it == sg_keyInstances.end()) {
        sg_keyInstances.push_back(KeyInstance(static_cast<Qt::Key>(k), InputRegistered));
    }
}

/***********************************************************************************/
void InputManager::registerKeyRelease(const int k) {

    if (auto it{FindKey(static_cast<Qt::Key>(k))}; it != sg_keyInstances.end()) {
        it->second = InputUnregistered;
    }
}

/***********************************************************************************/
void InputManager::registerMousePress(const Qt::MouseButton btn) {

    if (auto it{ FindButton(btn)}; it == sg_buttonInstances.end()) {
        sg_buttonInstances.push_back(ButtonInstance(btn, InputRegistered));
    }
}

/***********************************************************************************/
void InputManager::registerMouseRelease(const Qt::MouseButton btn) {

    if (auto it{FindButton(btn)}; it != sg_buttonInstances.end()) {
        it->second = InputUnregistered;
    }
}

/***********************************************************************************/
void InputManager::reset() {
    sg_keyInstances.clear();
    sg_buttonInstances.clear();
}
