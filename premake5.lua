workspace "Entite"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Entite"
	location "Entite"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENT_PLATFORM_WINDOWS",
			"ENTITE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

	filter "configurations:Debug"
		defines "ENT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENT_DIST"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

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
		"Entite/src"
	}

	links
	{
		"Entite"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENT_DIST"
		optimize "On"