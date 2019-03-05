#pragma once

#include "../Platform/PlatformUtils.h"

namespace Render {

///
[[nodiscard]] inline std::optional<bgfx::ShaderHandle> loadShader(const std::filesystem::path& shaderPath) {
	const auto& mem{ Platform::loadMemory(shaderPath) };

	if (!mem) {
		return std::nullopt;
	}

	return std::make_optional(bgfx::createShader(*mem));
}

///
[[nodiscard]] inline std::optional<bgfx::ProgramHandle> loadProgram(const std::filesystem::path& vsName,
																	const std::filesystem::path& fsName) {
	
	const auto& vs{ loadShader(vsName) };
	const auto& fs{ loadShader(fsName) };

	if (!vs || !fs) {
		return std::nullopt;
	}

	return std::make_optional(bgfx::createProgram(*vs, *fs, true));
}

} // namespace Render
