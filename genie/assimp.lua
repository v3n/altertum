--
-- Copyright (c) 2015 Jonathan Howard
-- MIT License
--

function assimp_library()
project "assimp"
    -- location (build_dir)
    -- targetdir (lib_dir)
    targetname "assimp"
    language "C++"
    kind "StaticLib"

    includedirs
    {
        ASSIMP_DIR .. "include/",
        ASSIMP_DIR .. "code/BoostWorkaround",
    }

    files
    {
        ASSIMP_DIR .. "code/**.cpp",
        ASSIMP_DIR .. "contrib/clipper/clipper.hpp",
        ASSIMP_DIR .. "contrib/clipper/clipper.cpp",
        ASSIMP_DIR .. "contrib/ConvertUTF/ConvertUTF.h",
        ASSIMP_DIR .. "contrib/ConvertUTF/ConvertUTF.c",
        ASSIMP_DIR .. "contrib/irrXML/**.h",
        ASSIMP_DIR .. "contrib/irrXML/**.cpp",
        ASSIMP_DIR .. "contrib/poly2tri/poly2tri/common/**.h",
        ASSIMP_DIR .. "contrib/poly2tri/poly2tri/common/**.cc",
        ASSIMP_DIR .. "contrib/poly2tri/poly2tri/sweep/**.h",
        ASSIMP_DIR .. "contrib/poly2tri/poly2tri/sweep/**.cc",
        ASSIMP_DIR .. "contrib/poly2tri/poly2tri/poly2tri.h",
        ASSIMP_DIR .. "contrib/unzip/**.h",
        ASSIMP_DIR .. "contrib/unzip/**.c",
        ASSIMP_DIR .. "contrib/zlib/**.h",
        ASSIMP_DIR .. "contrib/zlib/**.c",
        ASSIMP_DIR .. "include/assimp/**.hpp",
        ASSIMP_DIR .. "include/assimp/**.h"
    }

    configuration "windows"
        links 
        {
            "ole32"
        }

    configuration "linux"
        links
        {
            "dl"
        }

    configuration "macosx"
        links
        {
            "CoreServices.framework"
        }
end
