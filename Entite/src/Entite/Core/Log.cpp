#include "entpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Entite {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("ENTITE");
		s_CoreLogger->set_level(spdlog::level::level_enum::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_CoreLogger->set_level(spdlog::level::level_enum::trace);
	}
}