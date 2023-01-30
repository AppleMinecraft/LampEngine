project "LampEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
    systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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

    libdirs 
    { 
        "%{wks.location}/Libraries"
    }

	links
	{
		"glfw3.lib",
		"opengl32.lib"
	}

	filter "configurations:Debug"
		defines "LAMP_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LAMP_RELEASE"
		runtime "Release"
		optimize "on"