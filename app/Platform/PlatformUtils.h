#pragma once
#include <loguru/loguru.hpp>
#include <bgfx/bgfx.h>

#include <filesystem>
#include <optional>
#include <fstream>

namespace Platform {

///
[[nodiscard]] inline std::optional<const bgfx::Memory*> loadMemory(const std::filesystem::path& filePath) {
	namespace fs = std::filesystem;

	if (!fs::exists(filePath)) {
		LOG_F(INFO, "File not found: %S", filePath.c_str()); // %S for wide-char string instead of %s for narrow-char
		return std::nullopt;
	}

	std::ifstream file(filePath, std::ios::binary | std::ios::ate);
	const std::streamsize size{ file.tellg() };
	file.seekg(0, std::ios::beg);

	// Allocate memory
	const auto* mem{ bgfx::alloc(std::uint32_t(size + 1)) };

	// Read file into memory
	if (file.read( reinterpret_cast<char*>(mem->data), size)) {
		mem->data[mem->size - 1] = '\0';
		return std::make_optional(mem);
	}

	return std::nullopt;
}

} // namespace Platform