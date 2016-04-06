#include <gtest/gtest.h>
#include <core/CmdLine.h>
#include <string>
#include <vector>

using namespace altertum;

static std::vector<char *> args = 
{
    "altertum_tests",
    "-h",
    "--split-long-test",
    "1",
    "--uni-long-test=55",
    "-l",
    "50",
    ""
};

TEST(CmdLineTest, TestLongOpt)
{
    CmdLine * cmd = new CmdLine(args.size(), args.data(), nullptr);
    cmd->AddOption<char *>(nullptr, "split-long-test", nullptr, false,
        [](char * v) { ASSERT_STREQ(v, "1"); });
    cmd->AddOption<char *>(nullptr, "uni-long-test", nullptr, false,
        [](char * v) { ASSERT_STREQ(v, "55"); });
}

TEST(CmdLineTest, TestShortOp)
{
    CmdLine * cmd = new CmdLine(args.size(), args.data(), nullptr);
    cmd->AddOption<char *>("l", nullptr, nullptr, false,
        [](char * v) { ASSERT_STREQ(v, "50"); });
}

TEST(CmdLineTest, TestIntConvert)
{

}


