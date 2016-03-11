--
-- Copyright (c) 2015 Jonathan Howard.
--

function engine_project( _name, _kind, _defines )
project ( _name )
    kind (_kind)
    language "C++"

    vpaths
    {
        ["*"] = "src"
    }

    includedirs
    {
        ENG_DIR .. "src/",
        BGFX_DIR .. "examples/common",
        ENG_DIR .. "ext/luajit/src"
    }

    defines
    {
        "__WITH_SSE",
        _defines
    }

    links
    {
        "example-common",
        "bgfx",
        -- "assimp"
    }

    files
    {
        ENG_DIR .. "src/**.h",
        ENG_DIR .. "src/**.cpp",
    }

    configuration { "osx or ios" }
        files
        {
            path.join(BGFX_DIR, "examples/common/**.mm")
        }

    configuration {} -- reset config

    excludes
    {
        ENG_DIR .. "src/foundation/unit_test.cpp"
    }

    if not _OPTIONS["with-no-luajit"] then
        includedirs
        {
            ENG_DIR .. "ext/luajit/src",
        }

        configuration { "linux-* or osx" }
            links
            {
                "luajit"
            }

        configuration { "osx" }
            linkoptions
            {
                "-pagezero_size 10000",
                "-image_base 100000000"
            }
            libdirs
            {
                ENG_DIR .. "ext/luajit/lib/osx_x64"
            }
            postbuildcommands {
                "cp    " .. ENG_DIR .. "ext/luajit/lib/osx_x64/luajit " .. ENG_DIR .. "build/osx/bin",
                "cp -r " .. ENG_DIR .. "ext/luajit/src/jit " ..            ENG_DIR .. "build/osx/bin",
            }

        configuration { "x64", "linux-*" }
            libdirs
            {
                ENG_DIR .. "ext/luajit/lib/linux_x64"
            }
            links
            {
                "dl",
                "X11",
                "GL",
                "pthread"
            }
            postbuildcommands {
                "cp    " .. ENG_DIR .. "ext/luajit/lib/linux_x64/luajit " .. ENG_DIR .. "build/linux/bin",
                "cp -r " .. ENG_DIR .. "ext/luajit/src/jit " ..              ENG_DIR .. "build/linux/bin",
            }

        configuration { "vs*"}
            links
            {
                "lua51"
            }
            libdirs
            {
                ENG_DIR .. "ext/luajit/lib/win_x64"
            }

        configuration {} -- reset
    end

    configuration { "debug or development" }
        flags {
            "Symbols"
        }
        defines {
            "_DEBUG",
        }

    configuration { "release" }
        defines {
            "NDEBUG"
        }

    -- set build type defines
    configuration { "debug" }
        defines { "ALTERTUM_BUILD_TYPE=\"\\\"DEBUG\\\"\"" }
    configuration { "development" }
        defines { "ALTERTUM_BUILD_TYPE=\"\\\"DEV\\\"\"" }
    configuration { "release" }
        defines { "ALTERTUM_BUILD_TYPE=\"\\\"RELEASE\\\"\"" }

    configuration {}

    strip()

    configuration {}
end
