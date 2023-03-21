root = "../../../"

project "IMPLOT"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir (root .. "bin/" .. outputdir .. "/%{prj.name}")
	objdir (root .. "bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"implot.h",
		"implot.cpp",
		"implot_demo.cpp",
		"implot_internal.h",
		"implot_items.cpp"
	}

	disablewarnings
	{
		"26495"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		symbols "on"

	filter "configurations:Release"
		optimize "on"
