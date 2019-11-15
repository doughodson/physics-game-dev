--------------------------------------------------------
-- Example applications
--------------------------------------------------------

-- chapter 2: cannon
project "ch02-cannon"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "cannon"
   targetdir "../../ch02-cannon"
   debugdir "../../ch02-cannon"
   files {
      "../../ch02-cannon/**.h*",
      "../../ch02-cannon/**.c*",
      "../../ch02-cannon/**.rc"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- chapter 2: particle explosion
project "ch02-particle-explosion"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "particle-explosion"
   targetdir "../../ch02-particle-explosion"
   debugdir "../../ch02-particle-explosion"
   files {
      "../../ch02-particle-explosion/**.h*",
      "../../ch02-particle-explosion/**.c*",
      "../../ch02-particle-explosion/**.rc"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- chapter 4: cannon2
project "ch04-cannon2"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "cannon2"
   targetdir "../../ch04-cannon2"
   debugdir "../../ch04-cannon2"
   files {
      "../../ch04-cannon2/**.h*",
      "../../ch04-cannon2/**.c*",
      "../../ch04-cannon2/**.rc"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- chapter 9: rigid body 2D
project "ch09-rigid-body-2D"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "rigid-body-2D"
   targetdir "../../ch09-rigid-body-2D"
   debugdir "../../ch09-rigid-body-2D"
   files {
      "../../ch09-rigid-body-2D/**.h*",
      "../../ch09-rigid-body-2D/**.c*"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- chapter 15: flight simulator
project "ch15-flight-sim"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "flight-sim"
   targetdir "../../ch15-flight-sim"
   debugdir "../../ch15-flight-sim"
   files {
      "../../ch15-flight-sim/**.h*",
      "../../ch15-flight-sim/**.c*"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- chapter 17: hover
project "ch17-hover"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "hover"
   targetdir "../../ch17-hover"
   debugdir "../../ch17-hover"
   files {
      "../../ch17-hover/**.h*",
      "../../ch17-hover/**.c*"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")
