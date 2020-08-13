projectName = "EmeraldEngine"
projectMacroIdentifier = "EE"
interfaceName = "interfaceName"

workspace (projectName)
	architecture "x64"
	startproject "Sandbox"

	configurations {
		"Debug",
		"Release"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
latestCppDialect = "C++17"

pchName = "emeraldengine_pch"


include (projectName .. "/vendor/GLFW")


-- EmeraldEngine main module
project (projectName)
	location (projectName)
	kind "StaticLib"

	language "C++"
	cppdialect (latestCppDialect)
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader (pchName .. ".h")
	pchsource ("%{prj.name}/src/" .. pchName .. ".cpp")

	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/include"
	}
	
	links {
		"GLFW",
		"opengl32.lib"
	}

	postbuildcommands {
		"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"
		

	filter "configurations:Debug"
		defines {
			projectMacroIdentifier .. "_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines {
			projectMacroIdentifier .. "_RELEASE"
		}
		optimize "On"



-- Sandbox for testing
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"
	cppdialect (latestCppDialect)
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		projectName .. "/include"
	}

	links {
		projectName
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"
		

	filter "configurations:Debug"
		defines {
			projectMacroIdentifier .. "_DEBUG"
		}
		symbols "On"

	filter "configurations:Release"
		defines {
			projectMacroIdentifier .. "_RELEASE"
		}
		optimize "On"
