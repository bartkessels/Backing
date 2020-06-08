#pragma once

#include <string>

namespace backing::domain
{
    struct Request
    {
    public:
        std::string method;
        std::string baseUri;
        std::string resource;

        std::string completeUri() const {
            return baseUri + resource;
        }
    };
}