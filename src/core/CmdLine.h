/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <functional>
#include <string>
#include <cstdio>

namespace altertum
{

class CmdLine
{
public:
    CmdLine(const int _argc, const char ** const _argv, const char * description = nullptr)
        : m_argc(_argc)
        , m_argv(_argv)
    {
        help += _argv[0];
        if (description)
        {
            help += " - ";
            help += description;
            help += "\n\n";
        }
        else
        {
            help += "\n\n";
        }
    }

    ~CmdLine()
    {
    }

    template <typename T>
    void AddOption(
        char * short_name,
        char * long_name,
        char * help,
        std::function<void(T)> functor,
        bool required = false
        )
    {
        bool shouldHelp = true;
        help += "  ";

        if (short_name)
        {
            help += kShortOptPrefix + short_name;
        }

        if (long_name)
        {
            if (short_name) help += ",";
            help += kLongOptPrefix + long_name;
        }

        if (help)
        {
            help += "\t\t" + help;
        }

        help += "\n";

        for ( size_t i = 0; i < m_argc; i++ )
        {
            if (strncmpr(long_name, kLongOptPrefix, strlen(kLongOptPrefix)))
            {
                if (char * ptr = strchr(long_name, "="))
                {
                    shouldHelp = false;
                    SetOpt<T>(++ptr, functor);
                }
                else
                {
                    shouldHelp = false;
                    SetOpt<T>((++i < m_argc) ? m_argv[i] : nullptr, functor);
                }
            }
            else if (strncmpr(short_name, kShortOptPrefix, strlen(kShortOptPrefix)))
            {
                shouldHelp = false;
                SetOpt<T>((++i < m_argc) ? m_argv[i] : nullptr, functor);
            }
        }

        if (shouldHelp)
        {
            PrintHelp();
        }
    }

    void PrintHelp()
    {   printf("%s", help.c_str());
        exit(0);
    }

private:
    const char * kShortOptPrefix = "-";
    const char * kLongOptPrefix  = "--";

    void SetOpt(char * value, std::function<void(void)> functor)
    {
        functor();
    }

    void SetOpt(char * value, std::function<void(int)> functor)
    {
        int param = atoi(value);
        functor(param);
    }

    void SetOpt(char * value, std::function<void(float)> functor)
    {
        float param = (float)atof(value);
        functor(param);
    }

    void SetOpt(char * value, std::function<void(double)> functor)
    {
        double param = atof(value);
        functor(param);
    }

    void SetOpt(char * value, std::function<void(char *)> functor)
    {
        functor(value);
    }

    std::string help;

    const int m_argc;
    const char ** const m_argv;
};
}
