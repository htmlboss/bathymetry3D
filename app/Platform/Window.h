#pragma once

#include <bgfx/platform.h>

#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
	#define GLFW_EXPOSE_NATIVE_X11
	#define GLFW_EXPOSE_NATIVE_GLX
#elif BX_PLATFORM_OSX
	#define GLFW_EXPOSE_NATIVE_COCOA
	#define GLFW_EXPOSE_NATIVE_NSGL
#elif BX_PLATFORM_WINDOWS
	#define GLFW_EXPOSE_NATIVE_WIN32
	#define GLFW_EXPOSE_NATIVE_WGL
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <array>

struct AppDesc;
namespace Platform {
	struct PlatformUpdateData;
} // namespace Platform


namespace Platform {

class Window {
	friend static void windowIconifyCallback(GLFWwindow* win, int iconified);
	friend static void windowResizeCallback(GLFWwindow* win, int width, int height);
	friend static void windowKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods);
	friend static void windowDropCallback(GLFWwindow* win, int count, const char** paths);
	friend static void windowMousePositionCallback(GLFWwindow* win, double xPos, double yPos);

public:
	///
	bool init(struct AppDesc desc);
	///
	[[nodiscard]] PlatformUpdateData update() const;
	///
	void shutdown();

	///
	void resetTime();
	///
	bool shouldClose() const;

private:
	///
	void pollEvents() const;
	///
	inline static auto* getWindowPtr(GLFWwindow* window) {
		return static_cast<Window*>(glfwGetWindowUserPointer(window));
	}
	///
	inline static void windowResizeCallback(GLFWwindow* win, int width, int height) {
		auto* const window{ getWindowPtr(win) };
		
		window->m_isMinimized = false;
		if (width != 0 && height != 0) {

			window->m_winWidth = static_cast<std::uint32_t>(width);
			window->m_winHeight = static_cast<std::uint32_t>(height);
		}
	}
	///
	inline static void windowIconifyCallback(GLFWwindow* win, int iconified) {
		auto* const window{ getWindowPtr(win) };

		window->m_isMinimized = iconified == GLFW_TRUE;
	}
	///
	inline static void windowKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods) {
		auto* const window{ getWindowPtr(win) };

		const constexpr int RELEASED{ 0 };
		const constexpr int PRESSED{ 1 };		
		
		if (key >= 0 && key < 1024) {
			switch (action) {
			case PRESSED:
				window->m_keys[key] = true;
				break;
			case RELEASED:
				window->m_keys[key] = false;
				break;
			default:
				break;
			}
		}
	}
	///
	inline static void windowDropCallback(GLFWwindow* win, int count, const char** paths) {
		auto* const window{ getWindowPtr(win) };

		if (count == 0) {
			return;
		}
	}
	///
	inline static void windowMousePositionCallback(GLFWwindow* win, double xPos, double yPos) {
		auto* const window{ getWindowPtr(win) };

		window->m_mousePosX = xPos;
		window->m_mousePosY = yPos;
	}

	GLFWwindow* m_GLFWHandle{ nullptr };
	std::uint32_t m_winWidth{ 0 };
	std::uint32_t m_winHeight{ 0 };
	bool m_isMinimized{ false };
	bool m_isVSyncEnabled{ false };

	std::array<bool, 1024> m_keys;

	double m_mousePosX{ 0.0 }, m_mousePosY{ 0.0 };
};

} // namespace Platform