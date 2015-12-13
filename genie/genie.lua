--
-- Copyright (c) 2015 Jonathan Howard
--

ENG_DIR = (path.getabsolute("..") .. "/")

local ENG_EXT_DIR   = (ENG_DIR .. "ext/")
local ENG_BUILD_DIR = (ENG_DIR .. "build/")

BGFX_DIR    = (ENG_EXT_DIR .. "bgfx/")
BX_DIR      = (ENG_EXT_DIR .. "bx/")
BULLET_DIR  = (ENG_EXT_DIR .. "bullet3/")
ASSIMP_DIR  = (ENG_EXT_DIR .. "assimp/")

function copyLib()
end

newoption {
    trigger = "with-tools",
    description = "Build with tools."
}

newoption {
    trigger = "with-profiler",
    description = "Build with intrusive profiling."
}

solution "engine"
    configurations
    {
        "debug",
        "development",
        "release"
    }

    platforms
    {
        "x64",
        "native"
    }

    language "C++"

    configuration {}

dofile ("toolchain.lua")
dofile (BGFX_DIR .. "scripts/bgfx.lua")
dofile ("engine.lua")
dofile ("assimp.lua")
dofile ("bullet.lua")

toolchain (ENG_BUILD_DIR, ENG_EXT_DIR)

if _OPTIONS["with-profiler"] then
    defines {
        "ENTRY_CONFIG_PROFILER=1",
        "BGFX_CONFIG_PROFILER_REMOTERY=1",
        "_WINSOCKAPI_"
    }
end

group "libs"
bgfxProject("", "StaticLib", os.is("windows") and { "BGFX_CONFIG_RENDERER_DIRECT3D9=1" } or {})
dofile (BGFX_DIR .. "scripts/example-common.lua")
-- assimp_library()
bullet_library("StaticLib")

if _OPTIONS["with-tools"] then
    dofile ( BGFX_DIR .. "scripts/shaderc.lua" )
    dofile ( BGFX_DIR .. "scripts/geometryc.lua" )
    dofile ( BGFX_DIR .. "scripts/texturec.lua" )
end

group "engine"
engine_project("senior", "ConsoleApp", {})

configuration { "vs*" }
    local win_copy = function(p1, p2) return "xcopy \"" .. path.translate(p1) .. "\" \"" .. path.translate(p2) .. "\" /I /Q /S /E /Y /R" end
    prelinkcommands
    {
        win_copy(ENG_EXT_DIR .. "luajit/lib/win_x64/luajit.exe",    ENG_BUILD_DIR .. "windows/bin/"),
        win_copy(ENG_EXT_DIR .. "luajit/lib/win_x64/lua51.lib",    ENG_BUILD_DIR .. "windows/bin/"),
        win_copy(ENG_EXT_DIR .. "luajit/lib/win_x64/lua51.exp",    ENG_BUILD_DIR .. "windows/bin/"),
        win_copy(ENG_EXT_DIR .. "luajit/lib/win_x64/lua51.dll",    ENG_BUILD_DIR .. "windows/bin/"),
        win_copy(ENG_EXT_DIR .. "luajit/src/jit",                  ENG_BUILD_DIR .. "windows/bin/jit/")
    }
