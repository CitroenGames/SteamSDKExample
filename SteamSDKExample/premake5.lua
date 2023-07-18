project "SteamSDKExample"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "src/**.dll", "src/**.lib"}
   files { "**.dll", "**.lib"}
   files { "steam/**.h"}

   includedirs
   {
      "../Walnut/vendor/imgui",
      "../Walnut/vendor/glfw/include",
      "../Walnut/vendor/glm",
      "../Walnut/Walnut/src",
      "%{IncludeDir.VulkanSDK}",
      "../steam",
   }

   links
   {
       "Walnut",
       "steam_api",
       "steam_api64",
   }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   filter "system:windows"
      systemversion "latest"
      defines { "WL_PLATFORM_WINDOWS" }
      postbuildcommands 
      {
         "{COPY} %{cfg.buildtarget.directory}../steam/steam_api.dll %{cfg.buildtarget.directory}",
         "{COPY} %{cfg.buildtarget.directory}../steam/steam_api64.dll %{cfg.buildtarget.directory}"
      }

   filter "configurations:Debug"
      defines { "WL_DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "WL_RELEASE" }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "WL_DIST" }
      runtime "Release"
      optimize "On"
      symbols "Off"
