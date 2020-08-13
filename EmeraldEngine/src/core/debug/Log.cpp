#include "emeraldengine_pch.h"
#include "core/debug/Log.h"
#include "InternalLog.h"


namespace EmeraldEngine {
	// ---------------------
	// Logger initialization
	// ---------------------
	constexpr char* DEFAULT_LOGGER_PATTERN = "%^[%T] %n: %v%$";

	std::shared_ptr<spdlog::logger> createDefaultLogger(const char* name) {
		std::shared_ptr<spdlog::logger> spdlogLogger = spdlog::stdout_color_mt(name);
		spdlogLogger->set_pattern(DEFAULT_LOGGER_PATTERN);
		spdlogLogger->set_level(spdlog::level::trace);

		return spdlogLogger;
	}


	static std::shared_ptr<spdlog::logger> clientLog = createDefaultLogger("Client");
	static std::shared_ptr<spdlog::logger> coreLog = createDefaultLogger("Core");


	namespace ClientLog {
		std::shared_ptr<spdlog::logger> getLogger() {
			return clientLog;
		}
	}

	namespace InternalCoreLog {
		std::shared_ptr<spdlog::logger> getLogger() {
			return coreLog;
		}
	}
}
