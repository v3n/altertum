--
-- Copyright (c) 2015 Jonathan Howard.
--

function bullet_library(_kind)

newoption
{
    trigger = "without-cl",
    description = "Disable OpenCL for Bullet."
}

project "bullet"
    language "C++"
    kind(_kind)

    includedirs 
    {
        BULLET_DIR .. "src/"
    }

    files
    {
        BULLET_DIR .. "src/**.h",
        BULLET_DIR .. "src/**.cpp"
    }

if _OPTIONS["without-cl"] then
    excludes
    {
        BULLET_DIR .. "src/Bullet3OpenCL/**.cpp",
        BULLET_DIR .. "src/Bullet3OpenCL/**.h"
    }
end

end
