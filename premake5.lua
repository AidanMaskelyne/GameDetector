workspace "GameDetector"
	configurations { "Debug", "Release" }
	architecture "x86_64"

project "GameDetector"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir "target/%{cfg.buildcfg}-%{cfg.system}"
	objdir "target/%{cfg.buildcfg}-%{cfg.system}/obj"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"include",
	}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"