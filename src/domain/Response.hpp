#pragma once

#include <string>

namespace backing::domain
{
    struct Response
    {
    public:
        int statusCode;
        std::string contentType;
        std::string body;
    };
}