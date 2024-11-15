#pragma once

#include <memory>

#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
			#define ENT_PLATFORM_WINDOWS
	#else
			#error "x86 builds are not supported!"
	#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
	#include "TargetConditionals.h"

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator are not supported!"
	#elif
		#define ENT_PLATFROM_IOS
		#error "IOS is not supported!"
	#elif
		#define ENT_PLATFROM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown apple platform!"
	#endif

#elif defined(__ANDROIND__)
	#define ENT_PLATFROM_ANDROID
	#error "ANDROID is not supported!"
#elif defined(__linux__)
	#define ENT_PLATFROM_LINUX
	#error "LINUX is not supported!"
#else
	#error "Unknown platform!"
#endif // end of platform detection

#ifdef ENT_PLATFORM_WINDOWS
	#if ENT_DYNAMIC_LINK
		#ifdef ENTITE_BUILD_DLL
			#define ENTITE_API _declspec(dllexport)
		#else
			#define ENTITE_API _declspec(dllimport)
		#endif
	#else
		#define ENTITE_API
	#endif
#else
	#error "Entite only supports windows!"
#endif //ENT_PLATFORM_WINDOWS

#ifdef ENT_DEBUG
	#define ENT_ENABLE_ASSERTS
#endif // ENT_DEBUG

#ifdef ENT_ENABLE_ASSERTS
	#define ENT_ASSERT(x, ...) {if(!(x)) {ENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ENT_CORE_ASSERT(x, ...) {if(!(x)) {ENT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ENT_ASSERT(x, ...)
	#define ENT_CORE_ASSERT(x, ...)
#endif // ENT_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define ENT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Entite {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}


/*

#pragma once

#include <memory>

#ifdef ENT_PLATFORM_WINDOWS
#if ENT_DYNAMIC_LINK
	#ifdef ENTITE_BUILD_DLL
		#define ENTITE_API _declspec(dllexport)
	#else
		#define ENTITE_API _declspec(dllimport)
	#endif
#else
	#define ENTITE_API
#endif
#else
	#error ENTITE ONLY SUPPORTS WINDOWS!
#endif //ENT_PLATFORM_WINDOWS

#ifdef ENT_DEBUG
	#define ENT_ENABLE_ASSERTS
#endif // ENT_DEBUG

#ifdef ENT_ENABLE_ASSERTS
	#define ENT_ASSERT(x, ...) {if(!(x)) {ENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ENT_CORE_ASSERT(x, ...) {if(!(x)) {ENT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ENT_ASSERT(x, ...)
	#define ENT_CORE_ASSERT(x, ...)
#endif // ENT_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define ENT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Entite {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
*/