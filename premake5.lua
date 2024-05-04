workspace "Entite"
	architecture "x64"
	startproject "Game"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative the root folder (sol dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Entite/vendor/GLFW/include"
IncludeDir["Glad"] = "Entite/vendor/Glad/include"
--IncludeDir["ImGui"] = "Entite/vendor/imgui"
IncludeDir["ImGuiOrig"] = "Entite/vendor/imguiOrig"
IncludeDir["glm"] = "Entite/vendor/glm"

group "Dependencies"
	include "Entite/vendor/GLFW"
	include "Entite/vendor/Glad"
	--include "Entite/vendor/imgui"
	include "Entite/vendor/imguiOrig"

group ""

project "Entite"
	location "Entite"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "entpch.h"
	pchsource "Entite/src/entpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/glm/glm/**.cppm"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		--"%{IncludeDir.ImGui}"
		"%{IncludeDir.ImGuiOrig}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		--"ImGui",
		"ImGuiOrig",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		--cppdialect "C++17"
		--staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENT_PLATFORM_WINDOWS",
			"ENTITE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			--"_CRT_SECURE_NO_WARNINGS"
		}

		--postbuildcommands
		--{
			--("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Game/\"")
			-- old ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		--}

	filter "configurations:Debug"
		defines "ENT_DEBUG"
		--buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ENT_RELEASE"
		--buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ENT_DIST"
		--buildoptions "/MD"
		runtime "Release"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Entite/vendor/spdlog/include",
		"Entite/src",
		"Entite/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Entite"
	}

	filter "system:windows"
		--cppdialect "C++17"
		--staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENT_DEBUG"
		--buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ENT_RELEASE"
		--buildoptions "/MD"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ENT_DIST"
		--buildoptions "/MD"
		runtime "Release"
		optimize "on"