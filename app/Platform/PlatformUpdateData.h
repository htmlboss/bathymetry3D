#pragma once

#include "Keymap.h"

// https://softwareengineering.stackexchange.com/a/291808/142910
// https://gamedev.stackexchange.com/a/66819/74957
namespace Platform {
	
struct [[nodiscard]] PlatformUpdateData {
	PlatformUpdateData() {
		std::fill(Keymap.begin(), Keymap.end(), false);
	}
		
	std::uint32_t WindowWidth{ 0 }, WindowHeight{ 0 };
		
	bool WindowMinimized{ false };

	bool VSyncEnabled{ false };

	Keymap Keymap;

	double MousePosX{ 0.0 }, MousePosY{ 0.0 };
};

} // namespace Platform