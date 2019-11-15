--------------------------------------------------------
-- Example applications
--------------------------------------------------------

-- rigid body 2D
project "ch09-rigid-body-2D"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "rigid-body-2D"
   targetdir "../../ch09-rigid-body-2D"
   debugdir "../../ch09-rigid-body-2D"
   files {
      "../../ch09-rigid-body-2D/**.h*",
      "../../ch09-rigid-body-2D/**.cpp"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- flight simulator
project "ch15-flight-sim"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "flight-sim"
   targetdir "../../ch15-flight-sim"
   debugdir "../../ch15-flight-sim"
   files {
      "../../ch15-flight-sim/**.h*",
      "../../ch15-flight-sim/**.cpp"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- hover
project "ch17-hover"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "hover"
   targetdir "../../ch17-hover"
   debugdir "../../ch17-hover"
   files {
      "../../ch17-hover/**.h*",
      "../../ch17-hover/**.cpp"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")
