--
-- Copyright (c) 2015 Jonathan Howard
--

function build_tests(_kind)

local ENG_TEST_DIR = (ENG_DIR .. "test/")
local GTEST_DIR    = (ENG_EXT_DIR .. "googletest/googletest/")
local GMOCK_DIR    = (ENG_EXT_DIR .. "googletest/googlemock/")

project "tests"
    language "C++"
    kind("ConsoleApp")

    includedirs
    {
        GTEST_DIR .. "include/"
    }

    files
    {
        GTEST_DIR .. "src/gtest-all.cc",
        ENG_TEST_DIR .. "**.h",
        ENG_TEST_DIR .. "**.cpp"
    }
end

end