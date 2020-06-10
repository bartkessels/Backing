#pragma once

#include <string>

namespace backing::domain
{
    struct Logger
    {
    public:
        virtual ~Logger() = default;

        virtual void log(const std::string&) = 0;
    };
}