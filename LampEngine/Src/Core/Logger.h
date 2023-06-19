#pragma once
#include <memory>
#include <spdlog/spdlog.h>

namespace LampEngine {
	class Logger {
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger> GetEngineLogger();
		static std::shared_ptr<spdlog::logger> GetApplicationLogger();
	private:
		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_ApplicationLogger;
	};
}

#ifdef LAMPENGINE_PROJECT
#define __LAMP_LOGGER_PROFILE GetEngineLogger
#else
#define __LAMP_LOGGER_PROFILE GetApplicationLogger
#endif // LAMP_BUILD_DEBUG

#define LOGtrace(x, ...)    LampEngine::Logger::__LAMP_LOGGER_PROFILE()->trace(x, __VA_ARGS__)
#define LOGdebug(x, ...)    LampEngine::Logger::__LAMP_LOGGER_PROFILE()->debug(x, __VA_ARGS__)
#define LOGinfo(x, ...)     LampEngine::Logger::__LAMP_LOGGER_PROFILE()->info(x, __VA_ARGS__)
#define LOGwarn(x, ...)     LampEngine::Logger::__LAMP_LOGGER_PROFILE()->warn(x, __VA_ARGS__)
#define LOGerror(x, ...)    LampEngine::Logger::__LAMP_LOGGER_PROFILE()->error(x, __VA_ARGS__)
#define LOGcritical(x, ...) LampEngine::Logger::__LAMP_LOGGER_PROFILE()->critical(x, __VA_ARGS__)
