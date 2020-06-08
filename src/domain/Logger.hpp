#pragma once

#include <string>

namespace backing::domain
{
    struct Logger
    {
    public:
        virtual ~Logger() = default;

        virtual void log(std::string message) = 0;
    };
}