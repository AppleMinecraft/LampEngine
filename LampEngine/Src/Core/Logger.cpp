#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace LampEngine {
	std::shared_ptr<spdlog::logger> Logger::m_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::m_ApplicationLogger;
	void Logger::Init() {
		// Creating Logger
		spdlog::set_pattern("[%^%n %l%$]: %v");
		m_EngineLogger      = spdlog::stdout_color_mt("LampEngine");
		m_ApplicationLogger = spdlog::stdout_color_mt("Application");

		// Setting Log Level
		#ifdef LAMP_BUILD_DEBUG
		m_EngineLogger->set_level(spdlog::level::trace);
		m_ApplicationLogger->set_level(spdlog::level::trace);
		#endif
		#ifdef LAMP_BUILD_RELEASE
		m_EngineLogger->set_level(spdlog::level::info);
		m_ApplicationLogger->set_level(spdlog::level::info);
		#endif 
		LOGdebug("Logger Has Been Loaded.");
	}
	std::shared_ptr<spdlog::logger> Logger::GetEngineLogger() {
		return m_EngineLogger;
	}
	std::shared_ptr<spdlog::logger> Logger::GetApplicationLogger() {
		return m_ApplicationLogger;
	}
}