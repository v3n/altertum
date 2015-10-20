--
-- Copyright (c) 2015 Jonathan Howard.
--

function bullet_library(_kind)
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
end
