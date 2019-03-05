#include "App.h"
#include "AppDesc.h"
#include "Platform/PlatformUpdateData.h"
#include "Platform/Keyboard.h"

#include <loguru/loguru.hpp>

#include <bx/os.h>
#include <bgfx/bgfx.h>

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	}

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

/***********************************************************************************/
App::~App() {
	if (m_appInitialised) {
		bgfx::shutdown();
		m_win.shutdown();
	}
}

/***********************************************************************************/
bool App::init(const AppDesc& desc) {

	// Initialize window
	if (!m_win.init(desc)) {
		return false;
	}

	// Initialize bgfx
	if (!bgfx::init()) {
		return false;
	}

	bgfx::setDebug(BGFX_DEBUG_TEXT);

	// Set view 0 clear state.
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 0x0, 1.0f, 0);

	m_win.resetTime();

	// Create vertex stream declaration.
	PosColorVertex::init();

	LOG_F(INFO, "App initialised.");
	m_appInitialised = true;

	return true;
}

/***********************************************************************************/
void onRender(const uint32_t fbWidth, const uint32_t fbHeight, const float pxRatio) {
	bgfx::setViewRect(0, 0, 0, uint16_t(fbWidth), uint16_t(fbHeight));

	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::touch(0);

	// Use debug font to print information about this example.
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfxTemplate");
	bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Minimal bgfx + GLFW application.");
	bgfx::dbgTextPrintf(0, 4, 0x4f, "Press F1 to toggle bgfx stats, Esc to quit");
}

/***********************************************************************************/
void App::run() {
	if (!m_appInitialised) {
		LOG_F(ERROR, "App has not been initialised!");
		return;
	}

	m_timer.update();

	Platform::PlatformUpdateData prevPlatformUpdateData;

	bool showInternalStats{ false };

	/// https://github.com/JoshuaBrookover/bigg/blob/master/src/bigg_imgui.hpp

	while (!m_win.shouldClose()) {

		const auto& platformUpdateData{ m_win.update() };

		// If the window is minimized, sleep for 1 frame.
		if (platformUpdateData.WindowMinimized) {
			bx::sleep(16);
			continue;
		}

		const auto dt{ m_timer.getDelta() };

		if (Platform::keyWasPressed(GLFW_KEY_F1, platformUpdateData.Keymap, prevPlatformUpdateData.Keymap)) {
			showInternalStats = !showInternalStats;
			bgfx::setDebug(showInternalStats ? BGFX_DEBUG_STATS : BGFX_DEBUG_TEXT);
		}

		bgfx::reset(platformUpdateData.WindowWidth, platformUpdateData.WindowHeight, platformUpdateData.VSyncEnabled ? BGFX_RESET_VSYNC : BGFX_RESET_NONE);

		// Update and render
		onRender(platformUpdateData.WindowWidth, platformUpdateData.WindowHeight, platformUpdateData.WindowWidth / static_cast<float>(platformUpdateData.WindowHeight));

		// Advance to next frame.
		bgfx::frame();

		prevPlatformUpdateData = platformUpdateData;
	}
}
