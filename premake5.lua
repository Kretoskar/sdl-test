workspace "HC"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "App"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HCGame"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "vendor/SDL3/include"
    }

    libdirs {
        "vendor/SDL3/lib/x64"
    }

    links {
        "SDL3"
    }

    postbuildcommands {
         '{COPYFILE} "%{wks.location}/vendor/SDL3/lib/x64/SDL3.dll" "%{cfg.targetdir}"'
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"