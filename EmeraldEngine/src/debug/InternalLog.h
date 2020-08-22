#pragma once

// --- Standard library ---
#include <memory>

// --- External vendor libraries ---
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


namespace EmeraldEngine {
	namespace InternalCoreLog {
		std::shared_ptr<spdlog::logger> getLogger();
	};
}


// ----------------------------
// Logging macros for debugging
// ----------------------------
#ifdef EE_DEBUG

#define EE_CORE_LOG_TRACE(...) EmeraldEngine::InternalCoreLog::getLogger()->trace(__VA_ARGS__);
#define EE_CORE_LOG_INFO(...) EmeraldEngine::InternalCoreLog::getLogger()->info(__VA_ARGS__);
#define EE_CORE_LOG_WARN(...) EmeraldEngine::InternalCoreLog::getLogger()->warn(__VA_ARGS__);
#define EE_CORE_LOG_ERROR(...) EmeraldEngine::InternalCoreLog::getLogger()->error(__VA_ARGS__);
#define EE_CORE_LOG_CRITICAL(...) EmeraldEngine::InternalCoreLog::getLogger()->critical(__VA_ARGS__);

#else

#define EE_CORE_LOG_TRACE(...)
#define EE_CORE_LOG_INFO(...)
#define EE_CORE_LOG_WARN(...)
#define EE_CORE_LOG_ERROR(...)
#define EE_CORE_LOG_CRITICAL(...)

#endif
