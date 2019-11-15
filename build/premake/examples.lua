--------------------------------------------------------
-- Example applications
--------------------------------------------------------

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
