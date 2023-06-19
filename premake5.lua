outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

workspace "LampEngine"
	architecture "x86_64"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release"
	}

group "Core"
	include "LampEngine"
group ""
include "SandBox"