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
