project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	links
	{
		"LampEngine"
	}

    files
	{
		"src/**.h",
		"src/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{wks.location}/LampEngine/src",
		"%{wks.location}/Include",
	}

	filter "system:windows"
		systemversion "latest"

    filter "configurations:Debug"
		defines "LAMP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LAMP_RELEASE"
		runtime "Release"
		optimize "on"