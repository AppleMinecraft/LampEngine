#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace LampEngine {
	std::shared_ptr<spdlog::logger> Logger::ENGINE_LOGGER;
	std::shared_ptr<spdlog::logger> Logger::APPLICATION_LOGGER;

	void Logger::Init() {
		spdlog::set_pattern("[%^%n %l%$]: %v");

		ENGINE_LOGGER = spdlog::stdout_color_mt("LampEngine");
		APPLICATION_LOGGER = spdlog::stdout_color_mt("Application");

		ENGINE_LOGGER->set_level(spdlog::level::trace);
		APPLICATION_LOGGER->set_level(spdlog::level::trace);

		LOGdebug("Logger Has Been Loaded.");
	}
	std::shared_ptr<spdlog::logger> Logger::GetEngineLogger() {
		return ENGINE_LOGGER;
	}
	std::shared_ptr<spdlog::logger> Logger::GetApplicationLogger() {
		return APPLICATION_LOGGER;
	}
}