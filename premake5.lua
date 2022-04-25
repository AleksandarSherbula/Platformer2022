workspace "Platformer2022"
    configurations {"Debug", "Release"}
    startproject "Platformer2022"    

project "Platformer2022"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("build/bin/%{cfg.system}/%{cfg.build}")
    objdir("build/intermediate/%{cfg.system}/%{cfg.build}")

    files
	{
		"src/**.h",
		"src/**.cpp"
	}

    includedirs
	{        
		"external/json/include/",
	}
    
    filter "system:windows"
    systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"