#pragma once

#ifdef ENT_PLATFORM_WINDOWS
#ifdef ENTITE_BUILD_DLL
#define ENTITE_API _declspec(dllexport)
#else
#define ENTITE_API _declspec(dllimport)
#endif
#else
#error ENTITE ONLY SUPPORTS WINDOWS!
#endif //ENT_PLATFORM_WINDOWS


#ifdef ENT_ENABLE_ASSERTS
	#define ENT_ASSERT(x, ...) {if(!(x)) {ENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak; } }
	#define ENT_CORE_ASSERT(x, ...) {if(!(x)) {ENT_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak; } }
#else
	#define ENT_ASSERT(x, ...)
	#define ENT_CORE_ASSERT(x, ...)
#endif // ENT_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define ENT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)