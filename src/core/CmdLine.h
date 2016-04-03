/*
 * Copyright (c) 2015 Jonathan Howard
 * License: https://github.com/v3n/altertum/blob/master/LICENSE
 */

#pragma once

#include <functional>
#include <string>
#include <cstring>
#include <cstdio>

namespace altertum
{

class CmdLine
{
public:
    CmdLine(const int _argc, char ** _argv, const char * description)
        : m_argc(_argc)
        , m_argv(_argv)
    {
        m_help += _argv[0];
        if (description)
        {
            m_help += " - ";
            m_help += description;
            m_help += "\n\n";
        }
        else
        {
            m_help += "\n\n";
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
        m_help += "  ";

        if (short_name)
        {
            m_help += kShortOptPrefix;
            m_help += short_name;
        }

        if (long_name)
        {
            if (short_name) m_help += ",";
            m_help += kLongOptPrefix;
            m_help += long_name;
        }

        if (help)
        {
            m_help += "\t\t";
            m_help += help;
        }

        m_help += "\n";

        for ( size_t i = 0; i < m_argc; i++ )
        {
            if (strncmp(long_name, kLongOptPrefix, strlen(kLongOptPrefix)))
            {
                if (char * ptr = strchr(long_name, '='))
                {
                    shouldHelp = false;
                    SetOpt(++ptr, functor);
                }
                else
                {
                    shouldHelp = false;
                    SetOpt((++i < m_argc) ? m_argv[i] : nullptr, functor);
                }
            }
            else if (strncmp(short_name, kShortOptPrefix, strlen(kShortOptPrefix)))
            {
                shouldHelp = false;
                SetOpt((++i < m_argc) ? m_argv[i] : nullptr, functor);
            }
        }

        if (shouldHelp)
        {
            PrintHelp();
        }
    }

    void PrintHelp()
    {   printf("%s", m_help.c_str());
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

    std::string m_help;

    const int m_argc;
    char ** m_argv;
};
}
