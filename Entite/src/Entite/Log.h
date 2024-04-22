#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Entite {

	class ENTITE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}



// Core log macros
#define ENT_CORE_TRACE(...)		::Entite::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENT_CORE_INFO(...)		::Entite::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENT_CORE_WARN(...)		::Entite::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENT_CORE_ERROR(...)		::Entite::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENT_CORE_FATAL(...)		::Entite::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define ENT_TRACE(...)      ::Entite::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENT_INFO(...)		::Entite::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENT_WARN(...)		::Entite::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENT_ERROR(...)		::Entite::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENT_FATAL(...)		::Entite::Log::GetClientLogger()->fatal(__VA_ARGS__)