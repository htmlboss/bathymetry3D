#pragma once

#include "Keymap.h"

namespace Platform {
///
[[nodiscard]] inline auto keyWasPressed(const std::size_t key, const Keymap& currentKeymap, const Keymap& prevKeymap) {
	return currentKeymap[key] && !prevKeymap[key];
}
///
[[nodiscard]] inline auto keyWasHeld(const std::size_t key, const Keymap& currentKeymap) {
	return currentKeymap[key];
}

} // namespace Platform
