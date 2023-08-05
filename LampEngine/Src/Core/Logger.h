#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace LampEngine {

	// Use Logger Macros instead of this class
	class Logger {
	public:
		// Creates the logger, instead it calling this call the Core::Init() method
		static void Init();

		// Returns the Engine logger
		static std::shared_ptr<spdlog::logger> GetEngineLogger();
		// Returns the Application logger
		static std::shared_ptr<spdlog::logger> GetApplicationLogger();
	private:
		static std::shared_ptr<spdlog::logger> ENGINE_LOGGER;
		static std::shared_ptr<spdlog::logger> APPLICATION_LOGGER;
	};
}

// Figure out if we are in Engine our client application
#ifdef LAMPENGINE_PROJECT
	// If we are in Engine set the logger to Engine Logger.
	#define __LAMP_LOGGER_PROFILE GetEngineLogger
#else
	// If we are in Client Application set the logger to Application Logger.
	#define __LAMP_LOGGER_PROFILE GetApplicationLogger
#endif

// LOGGER MACROS
#define LOGtrace(x, ...)    LampEngine::Logger::__LAMP_LOGGER_PROFILE()->trace(x, __VA_ARGS__)
#define LOGdebug(x, ...)    LampEngine::Logger::__LAMP_LOGGER_PROFILE()->debug(x, __VA_ARGS__)
#define LOGinfo(x, ...)     LampEngine::Logger::__LAMP_LOGGER_PROFILE()->info(x, __VA_ARGS__)
#define LOGwarn(x, ...)     LampEngine::Logger::__LAMP_LOGGER_PROFILE()->warn(x, __VA_ARGS__)
#define LOGerror(x, ...)    LampEngine::Logger::__LAMP_LOGGER_PROFILE()->error(x, __VA_ARGS__)
#define LOGcritical(x, ...) LampEngine::Logger::__LAMP_LOGGER_PROFILE()->critical(x, __VA_ARGS__)

// In Release Mode Remove LogTrace and LogDebug for better performance.
#ifdef LAMP_BUILD_RELEASE
	// Removing the defination
	#undef LOGtrace
	#undef LOGdebug
	// Redefine as nothing
	#define LOGtrace
	#define LOGdebug
#endif