--
-- Copyright (c) 2015 Jonathan Howard
--

ENG_DIR = (path.getabsolute("..") .. "/")

local ENG_EXT_DIR   = (ENG_DIR .. "ext/")
local ENG_BUILD_DIR = (ENG_DIR .. "build/")

BGFX_DIR    = (ENG_EXT_DIR .. "bgfx/") 
BX_DIR      = (ENG_EXT_DIR .. "bx/")
ASSIMP_DIR  = (ENG_EXT_DIR .. "assimp/")

function copyLib()
end

newoption {
    trigger = "with-tools",
    description = "Build with tools."
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

toolchain (ENG_BUILD_DIR, ENG_EXT_DIR)

group "libs"
bgfxProject("", "StaticLib", os.is("windows") and { "BGFX_CONFIG_RENDERER_DIRECT3D9=1" } or {})
dofile (BGFX_DIR .. "scripts/example-common.lua")
assimp_library()

if _OPTIONS["with-tools"] then
    dofile ( "shaderc.lua" )
end

group "engine"
engine_project("senior", "ConsoleApp", {})
