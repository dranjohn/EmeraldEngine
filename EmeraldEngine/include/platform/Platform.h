#pragma once

namespace EmeraldEngine {
	enum class Platform {
		missingPlatform,
		defaultPlatform,
		opengl
	};

	Platform getPlatform();
}
