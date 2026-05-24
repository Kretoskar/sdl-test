workspace "HC"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "App"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HCCore"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
	{
        "src/HCCore/src/**.h",
        "src/HCCore/src/**.hpp",
        "src/HCCore/src/**.cpp",
		"src/HCCore/include/**.h",
        "src/HCCore/include/**.hpp",
    }

    includedirs 
	{
        "src/HCCore/include",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"
		
project "HCEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
	{
        "src/HCEngine/src/**.h",
        "src/HCEngine/src/**.hpp",
        "src/HCEngine/src/**.cpp",
		"src/HCEngine/include/HCEngine/**.h",
        "src/HCEngine/include/HCEngine/**.hpp",
    }

    includedirs 
	{
		"src/HCCore/include/",
		"src/HCEngine/include",
        "vendor/SDL3/include",
        "vendor/SDL3_image/include"
    }

    libdirs 
	{
        "vendor/SDL3/lib/x64",
        "vendor/SDL3_image/lib/x64"
    }
	
	dependson { "FFCore" }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"

project "HCGame"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
	{
        "src/HCGame/src/**.h",
        "src/HCGame/src/**.hpp",
        "src/HCGame/src/**.cpp",
		"src/HCGame/include/**.h",
        "src/HCGame/include/**.hpp",
    }

    includedirs 
	{
        "vendor/SDL3/include",
        "vendor/SDL3_image/include",
		"src/HCCore/include",
		"src/HCEngine/include",
    }

    libdirs 
	{
        "vendor/SDL3/lib/x64",
        "vendor/SDL3_image/lib/x64"
    }

    links 
	{
        "SDL3",
        "SDL3_image",
		"HCCore",
		"HCEngine"
    }
	
	dependson { "FFCore", "FFEngine" }
	
	defines 
	{
		'ASSETS_DIR="%{wks.location}/assets"'
	}

    postbuildcommands 
	{
         '{COPYFILE} "%{wks.location}/vendor/SDL3/lib/x64/SDL3.dll" "%{cfg.targetdir}"',
         '{COPYFILE} "%{wks.location}/vendor/SDL3_image/lib/x64/SDL3_image.dll" "%{cfg.targetdir}"',
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"