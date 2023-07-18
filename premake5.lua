-- premake5.lua
workspace "SteamSDKExample"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SteamSDKExample"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "SteamSDKExample"