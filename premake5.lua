workspace "LampEngine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.system}-%{cfg.buildcfg}-%{cfg.architecture}"

group "Dependencies"
group ""

group "Core"
	include "LampEngine"
group ""

include "Sandbox"
