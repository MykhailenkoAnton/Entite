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
