-- premake5.lua
workspace "Genesis"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Genesis"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "Genesis"