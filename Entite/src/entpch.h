#pragma once

//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Entite/Core/Log.h"
#include "Entite/Debug/Instrumentor.h"

#ifdef ENT_PLATFORM_WINDOWS
#include "Windows.h"
#endif // ENT_PLATFORM_WINDOWS
