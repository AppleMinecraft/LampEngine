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
		"%{prj.location}/**.h",
		"%{prj.location}/**.cpp",
		"%{prj.location}/**.hpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"LAMPENGINE_PROJECT"
	}

	includedirs
	{
        "%{wks.location}/Includes",
		"%{prj.location}/Src",
		"%{prj.location}/Vendor",
		"%{prj.location}"
	}

    libdirs 
    { 
        "%{wks.location}/Libraries" 
    }

	links
	{
		"opengl32.lib",
        "glfw3.lib",
		"spdlog.lib"
	}

	filter "configurations:Debug"
		defines "LAMP_BUILD_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LAMP_BUILD_RELEASE"
		runtime "Release"
		optimize "on"