--
-- If premake command is not supplied an action (target compiler), exit!
--
-- Target of interest:
--     vs2019     (Visual Studio 2019)
--

-- we must have an ide/compiler specified
if (_ACTION == nil) then
  return
end

--
-- set include and library paths
--
DX7_IncPath         = "c:/apps/dx7-sdk/include"
DX7_LibPath         = "c:/apps/dx7-sdk/lib"

COMMON_IncPath      = "../../"

--
-- 3rd party library names
--
LibDX7     = { "d3drm.lib", "ddraw.lib" }
LibWindows = { "Winmm" }

local function createConsoleProject(targetDirPath, targetName)
   project (targetName)
     kind("ConsoleApp")
     defines({"_CONSOLE"})
     location("../" .. _ACTION .. "/projects/%{prj.name}")
     targetname(targetName)
     targetdir("../../" .. targetDirPath)
     includedirs({COMMON_IncPath})
     debugdir("../../" .. targetDirPath)
     files({
        "../../" .. targetDirPath .. "/**.h*",
        "../../" .. targetDirPath .. "/**.c*"
     })
     excludes({
        "../../" .. targetDirPath .. "/winmain.cpp",
        "../../" .. targetDirPath .. "/d3d*.*"
     })
     links({LibWindows})
end

local function createMFCProject(targetDirPath, targetName)
   project (targetName)
     kind("WindowedApp")
     location("../" .. _ACTION .. "/projects/%{prj.name}")
     targetname(targetName)
     includedirs({DX7_IncPath, COMMON_IncPath})
     targetdir("../../" .. targetDirPath)
     debugdir("../../" .. targetDirPath)
     files({
        "../../" .. targetDirPath .. "/**.h*",
        "../../" .. targetDirPath .. "/**.c*",
        "../../" .. targetDirPath .. "/**.rc"
     })
     excludes({
        "../../" .. targetDirPath .. "/main.cpp"
     })
     libdirs({ DX7_LibPath })
     links({ LibDX7, LibWindows })
end

workspace("physics-game-dev")

   location("../" .. _ACTION)

   -- configuration shared between all projects
   language("C++")
   characterset("MBCS")

   --
   -- Build (solution) configuration options:
   --     Release        (Application linked to Multi-threaded DLL)
   --     Debug          (Application linked to Multi-threaded Debug DLL)
   --
   configurations({ "Release", "Debug" })

   -- visual studio options and warnings
   -- /wd4351 (C4351 warning) - disable warning associated with array brace initialization
   -- /wd4996 (C4996 warning) - disable deprecated declarations
   -- /wd4005 (C4005 warning) - disable macro redefinition
   -- /wd4100 (C4100 warning) - disable unreferenced formal parameter
   -- /Oi - generate intrinsic functions
   disablewarnings({ "4351",  "4996", "4005", "4100" })
   buildoptions({ "/Oi" })

   -- common release configuration flags, symbols and libraries
   filter({ "configurations:Release" })
      optimize("On")
      -- favor speed over size
      buildoptions { "/Ot" }
      defines { "WIN32", "NDEBUG" }

   -- common debug configuration flags, symbols and libraries
   filter({ "configurations:Debug" })
      symbols("On")
      targetsuffix("_d")
      defines { "WIN32", "_DEBUG" }

   project "common"
      kind("None")
      location("../" .. _ACTION .. "/projects/%{prj.name}")
      targetname "common"
      files {
         "../../common/**.h*",
         "../../common/**.c*"
      }

   createMFCProject("ch02-cannon", "cannon")
   createMFCProject("ch02-particle-explosion", "particle-explosion")
   createMFCProject("ch04-cannon2", "cannon2")
   createMFCProject("ch06-cannon3", "cannon3")
   createMFCProject("ch08-falling-particles", "falling-particles")
   createMFCProject("ch09-rigid-body-2D", "rigid-body-2D")
   createMFCProject("ch13-cloth-sim", "cloth-sim")
   createMFCProject("ch17-hover", "hover")

   createConsoleProject("chXX-volume", "volume")

   createMFCProject("ch15-flight-sim", "flight-sim_dx7")
   createConsoleProject("ch15-flight-sim", "flight-sim")

