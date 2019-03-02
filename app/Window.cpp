#include "Window.h"
#include "AppDesc.h"
#include "Keyboard.h"
#include "PlatformUpdateData.h"

#include <loguru/loguru.hpp>

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
#include <GLFW/glfw3native.h>

namespace Platform {

///
void windowErrorCallback(int error, const char* desc) {
	LOG_F(ERROR, desc);
}

///
void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key >= 0 && key < 1024) {
		switch (action) {
		case 1: // Pressed
			Keyboard::instance().m_keys[key] = true;
			break;
		case 0: // Released
			Keyboard::instance().m_keys[key] = false;
			break;
		default:
			break;
		}
	}
}

///
void windowResizeCallback(GLFWwindow* window, int width, int height) {
	auto* win{ reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)) };

	win->m_isMinimized = false;
	if (width != 0 && height != 0) {

		win->m_winWidth = static_cast<uint32_t>(width);
		win->m_winHeight = static_cast<uint32_t>(height);
	}
}

///
void windowIconifyCallback(GLFWwindow* window, int iconified) {
	auto* win{ reinterpret_cast<Window*>(glfwGetWindowUserPointer(window)) };

	win->m_isMinimized = iconified == GLFW_TRUE; // Don't reset bgfx because when the window is restored we don't know the correct window dimensions.
}

bool Window::init(const AppDesc desc) {

	glfwSetErrorCallback(windowErrorCallback);
	if (!glfwInit()) {
		LOG_F(ERROR, "Failed to initialise GLFW.");
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	auto* monitor{ glfwGetPrimaryMonitor() };
	const auto* mode{ glfwGetVideoMode(monitor) };

	glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_ALPHA_BITS, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_DEPTH_BITS, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

#if BX_PLATFORM_OSX
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	if (desc.Fullscreen) {
		const auto nativeResolution{ desc.WindowWidth <= 0 || desc.WindowHeight <= 0 };
		
		const auto width{ nativeResolution ? mode->width : desc.WindowWidth };
		const auto height{ nativeResolution ? mode->height : desc.WindowHeight };
		
		m_GLFWHandle = glfwCreateWindow(width, height, desc.AppTitle, monitor, nullptr);

		if (!m_GLFWHandle) {
			return false;
		}
	} 
	else {
		m_GLFWHandle = glfwCreateWindow(desc.WindowWidth, desc.WindowHeight, desc.AppTitle, nullptr, nullptr);
		
		if (!m_GLFWHandle) {
			return false;
		}

		glfwSetWindowPos(m_GLFWHandle, (mode->width - desc.WindowWidth) / 2, (mode->height - desc.WindowHeight) / 2);
	}

	glfwSetWindowUserPointer(m_GLFWHandle, this);

	// Set callbacks
	glfwSetKeyCallback(m_GLFWHandle, windowKeyCallback);
	glfwSetWindowSizeCallback(m_GLFWHandle, windowResizeCallback);
	glfwSetWindowIconifyCallback(m_GLFWHandle, windowIconifyCallback);

	{
		bgfx::PlatformData pd;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		pd.ndt = glfwGetX11Display();
		pd.nwh = (void*)(uintptr_t)glfwGetX11Window(m_GLFWHandle);
#elif BX_PLATFORM_OSX
		pd.ndt = nullptr;
		pd.nwh = glfwGetCocoaWindow(m_GLFWHandle);
#elif BX_PLATFORM_WINDOWS
		pd.ndt = nullptr;
		pd.nwh = glfwGetWin32Window(m_GLFWHandle);
#endif
		pd.context = nullptr;
		pd.backBuffer = nullptr;
		pd.backBufferDS = nullptr;
		bgfx::setPlatformData(pd);
	}

	return true;
}

PlatformUpdateData Window::update() const {
	if (Keyboard::instance().isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(m_GLFWHandle, GLFW_TRUE);
	}
}

void Window::shutdown() {
	LOG_F(INFO, "Shutting down GLFW.");
	glfwTerminate();
}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::resetTime() {
	glfwSetTime(0.0);
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(m_GLFWHandle);
}

} // namespace Platform