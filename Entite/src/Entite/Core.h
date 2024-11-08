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