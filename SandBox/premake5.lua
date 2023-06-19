project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
    systemversion "latest"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/Src/**.h",
		"%{prj.location}/Src/**.cpp",
	}

    includedirs
	{
        "%{wks.location}/Includes",
		"%{wks.location}/LampEngine/Src",
		"%{wks.location}/LampEngine/Vendor",
		"%{wks.location}/LampEngine",
		"%{prj.location}/Src"
    }

	links
	{
		"LampEngine"
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines "LAMP_BUILD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LAMP_BUILD_RELEASE"
		runtime "Release"
		optimize "on"