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
        _defines
    }

    links
    {
        "example-common",
        "bgfx"
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
            libdirs
            {
                ENG_DIR .. "ext/luajit/lib/osx_x64"
            }

        configuration { "x64", "linux-*" }
            libdirs
            {
                ENG_DIR .. "ext/luajit/lib/linux_x64"
            }

        configuration { "vs*"}
            links
            {
                "lua51"
            }

        configuration { "x32", "vs*" }
            libdirs
            {
                ENG_DIR .. "ext/luajit/lib/win_x86"
            }

        configuration { "x64", "vs*" }
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

    configuration {}

    files 
    {
        ENG_DIR .. "src/**.h",
        ENG_DIR .. "src/*.cpp",
        path.join(BGFX_DIR, "examples/common/**.mm"),
    }

    strip()

    configuration {}
end
