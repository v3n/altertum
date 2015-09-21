--
-- Copyright (c) 2015 Jonathan Howard
-- MIT License
--

function fswatch_library()
local LIBFSWATCH_SRC_DIR = FSWATCH_DIR .. "libfswatch/src/libfswatch/"

project "fswatch"
    targetname "fswatch"
    language "C++"
    kind "StaticLib"

    removeflags { "NoExceptions" }

    defines
    {
        "HAVE_CXX_MUTEX=1",
        "HAVE_CXX_UNIQUE_PTR=1"
    }

    files 
    {
        LIBFSWATCH_SRC_DIR .. "c++/event.cpp",
        LIBFSWATCH_SRC_DIR .. "c++/monitor.cpp",
        LIBFSWATCH_SRC_DIR .. "c++/libfswatch_exception.cpp",
        LIBFSWATCH_SRC_DIR .. "c++/path_utils.cpp",
        LIBFSWATCH_SRC_DIR .. "c++/**.h",
    }

    includedirs
    {
        LIBFSWATCH_SRC_DIR .. "/"
    }

    configuration { "not windows" }
        files { LIBFSWATCH_SRC_DIR .. "c++/poll_monitor.cpp" }

    configuration { "gmake" }
        buildoptions { "-std=c++11" }

    configuration { "osx" }
        linkoptions { "-stdlib=libc++" }
        files { LIBFSWATCH_SRC_DIR .. "c++/fsevents_monitor.*" }

    configuration { "linux" }
        defines { "HAVE_STRUCT_STAT_ST_MTIME" }
        files { LIBFSWATCH_SRC_DIR .. "c++/inotify_monitor.cpp" }

    configuration { "osx or bsd" }
        defines { "HAVE_STRUCT_STAT_ST_MTIMESPEC" }

    configuration { "bsd" }
        files { LIBFSWATCH_SRC_DIR .. "c++/kqueue_monitor.cpp" }


end
