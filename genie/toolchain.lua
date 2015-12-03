--
-- Copyright (c) 2015 Jonathan Howard, Daniele Bartolini
-- MIT License
--

function toolchain(build_dir, lib_dir)

    newoption
    {
        trigger = "compiler",
        value = "COMPILER",
        description = "Choose compiler",
        allowed =
        {
            { "osx", "Clang - OS X" },
            { "linux-gcc", "Linux (GCC compiler)" },
            { "linux-clang", "Linux (Clang compiler)" }
        }
    }

    if (_ACTION == nil) then return end

    location ( build_dir .. "projects/" .. _ACTION )

    if _ACTION == "clean" then
        os.rmdir(BUILD_DIR)
    end

    if _ACTION == "gmake" then
        if nil == _OPTIONS["compiler"] then
            print("No compiler selected.")
            os.exit(1)
        end

        if "linux-gcc" == _OPTIONS["compiler"] or "linux-clang" == _OPTIONS["compiler"] then
            if not os.is("linux") then
                print("Action not valid in current OS.")
            end

            location(build_dir .. "projects/" .. "linux")
        end

        if "osx" == _OPTIONS["compiler"] then
            if not os.is("macosx") then
                print("Action not valid in current OS.")
            end

            location(build_dir .. "projects/" .. "osx")
        end

        if "osx" == _OPTIONS["compiler"] or "linux-clang" == _OPTIONS["compiler"] then
            premake.gcc.cc = "clang"
            premake.gcc.cxx = "clang++"
            premake.gcc.ar = "ar"
        end
    end

    if _ACTION == "vs2013" then
        if not os.is("windows") then
            print("Action not valid in current OS.")
        end

        location(build_dir .. "projects/" .. _ACTION)
    end

    flags
    {
        "StaticRuntime",
        "NoPCH",
        "NoRTTI",
        "NoExceptions",
        "NoEditAndContinue",
        "Symbols"
    }

    includedirs
    {
        BGFX_DIR .. "include/",
        BX_DIR .. "include/"
    }

    defines {
    	"__STDC_FORMAT_MACROS",
    	"__STDC_CONSTANT_MACROS",
    	"__STDC_LIMIT_MACROS",
	}

    configuration { "gmake" }
        buildoptions
        {
            "-m64"
        }
        buildoptions_cpp
        {
            "-std=c++11"
        }

    configuration { "development or release" }
        flags
        {
            "OptimizeSpeed"
        }

    configuration { "debug", "native" }
        targetsuffix "-debug"

    configuration { "development", "native" }
        targetsuffix "-development"

    configuration { "release", "native" }
        targetsuffix "-release"

    configuration { "vs*" }
        targetdir( build_dir .. "windows/bin" )
        objdir( build_dir .. "windows/obj" )

        includedirs { BX_DIR .. "include/compat/msvc" }
        defines {
            "WIN32",
            "_WIN32",
            "_HAS_EXCEPTIONS=0",
            "_HAS_ITERATOR_DEBUGGING=0",
            "_SCL_SECURE=0",
            "_SECURE_SCL=0",
            "_SCL_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_DEPRECATE",
            "NOMINMAX",
        }
        buildoptions {
            "/Oy-", -- Suppresses creation of frame pointers on the call stack.
            "/Ob2", -- The Inline Function Expansion
        }
        linkoptions {
            "/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
            "/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
            "/ignore:4099", -- LNK4099: The linker was unable to find your .pdb file.
        }

    configuration { "osx" }
        targetdir( build_dir .. "osx/bin" )
        objdir( build_dir .. "osx/obj" )

        libdirs
        {
            build_dir .. "osx/bin"
        }

        links
        {
            "Cocoa.framework",
            "CoreVideo.framework",
            "IOKit.framework",
            "OpenGL.framework",
            "QuartzCore.framework",
            "Metal.framework"
        }

        includedirs { BX_DIR .. "include/compat/osx" }


    configuration {} --reset config
end

function strip()
    configuration { "android-arm", "release"}
        postbuildcommands {
            "$(SILENT) echo Stripping symbols",
            "$(SILENT) $(ANDROID_NDK_ARM)/bin/arm-linux-androideabi-strip -s \"$(TARGET)\""
        }

    configuration { "linux-*", "release" }
        postbuildcommands {
            "$(SILENT) echo Stripping symbols",
            "$(SILENT) strip -s \"$(TARGET)\""
        }

    configuration {} -- reset configuration
end
