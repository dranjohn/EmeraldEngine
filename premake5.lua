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


-- GLAD
include (projectName .. "/vendor/glad")


--GLFW
glfwLocation = "EmeraldEngine/vendor/glfw"

project "GLFW"
	location (glfwLocation)
	kind "StaticLib"
	
	language "C"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files {
		glfwLocation.."/include/GLFW/glfw3.h",
		glfwLocation.."/include/GLFW/glfw3native.h",
		glfwLocation.."/src/glfw_config.h",
		glfwLocation.."/src/context.c",
		glfwLocation.."/src/init.c",
		glfwLocation.."/src/input.c",
		glfwLocation.."/src/monitor.c",
		glfwLocation.."/src/vulkan.c",
		glfwLocation.."/src/window.c"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files {
			glfwLocation.."/src/win32_init.c",
			glfwLocation.."/src/win32_joystick.c",
			glfwLocation.."/src/win32_monitor.c",
			glfwLocation.."/src/win32_time.c",
			glfwLocation.."/src/win32_thread.c",
			glfwLocation.."/src/win32_window.c",
			glfwLocation.."/src/wgl_context.c",
			glfwLocation.."/src/egl_context.c",
			glfwLocation.."/src/osmesa_context.c"
		}

		defines { 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"


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
		"%{prj.name}/include",
		"%{prj.name}/vendor/glad/include",
		"%{prj.name}/vendor/glfw/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb/include",
		"%{prj.name}/vendor/glm/glm"
	}
	
	links {
		"GLAD",
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
		projectName .. "/include",
		projectName .. "/vendor/spdlog/include"
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
