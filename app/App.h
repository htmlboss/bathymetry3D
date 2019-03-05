#pragma once

#include "Platform/Window.h"
#include "Timer.h"

/***********************************************************************************/
// Forward declarations
struct AppDesc;

// https://github.com/ocornut/imgui/issues/707#issuecomment-463758243

/***********************************************************************************/
class App {
	
public:
	App() = default;
	~App();

	App(App&&) = delete;
	App(const App&) = delete;

	App& operator=(App&&) = delete;
	App& operator=(const App&) = delete;

	///
	bool init(const AppDesc& desc);
	///
	void run();

private:

	bool m_appInitialised{ false };

	Platform::Window m_win;
	Timer m_timer;
};
