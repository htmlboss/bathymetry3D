#pragma once

struct AppDesc {
	const char* AppTitle{ "Bathymetry3D" };
	bool Fullscreen{ false };
	int WindowWidth{ 1280 }, WindowHeight{ 720 }; // Negative values will result in native resolution
};
