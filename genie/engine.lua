--
-- Copyright (c) 2015 Jonathan Howard.
--

function engine_project( _name, _kind, _defines )
project ( _name )
    kind (_kind)

    includedirs 
    {
        ENG_DIR .. "src/",
        BGFX_DIR .. "examples/common"
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
        "assimp"
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
            postbuildcommands {
                "cp    " .. ENG_DIR .. "ext/luajit/lib/linux_x64/luajit " .. ENG_DIR .. "build/linux/bin",
                "cp -r " .. ENG_DIR .. "ext/luajit/src/jit " ..              ENG_DIR .. "build/linux/bin",
            }

        configuration { "vs*"}
            links
            {
                "lua51"
            }

        -- configuration { "x32", "vs*" }
        --     libdirs
        --     {
        --         ENG_DIR .. "ext/luajit/lib/win_x86"
        --     }

        configuration { "vs*" }
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

    files 
    {
        ENG_DIR .. "src/**.h",
        ENG_DIR .. "src/**.cpp",
        path.join(BGFX_DIR, "examples/common/**.mm"),
    }

    excludes
    {
        ENG_DIR .. "src/foundation/unit_test.cpp"
    }

    strip()

    configuration {}
end
