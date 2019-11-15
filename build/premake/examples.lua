--------------------------------------------------------
-- Example applications
--------------------------------------------------------

-- flight simulator
project "chap15-flight-sim"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "flight-sim"
   targetdir "../../chap15-flight-sim"
   debugdir "../../chap15-flight-sim"
   files {
      "../../chap15-flight-sim/**.h*",
      "../../chap15-flight-sim/**.cpp"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")

-- hover
project "chap17-hover"
   kind "WindowedApp"
--   kind "ConsoleApp"
--   defines { "_CONSOLE" }
   targetname "hover"
   targetdir "../../chap17-hover"
   debugdir "../../chap17-hover"
   files {
      "../../chap17-hover/**.h*",
      "../../chap17-hover/**.cpp"
   }
   includedirs { DX7_IncPath }
   libdirs     { DX7_LibPath }
   links { LibDX7, LibWindows }
   characterset("MBCS")
