#pragma once

#include <map>
#include <string>

namespace backing::domain
{
    struct Response
    {
    public:
        int statusCode;
        std::map<std::string, std::string> headers;
        std::string body;

        [[nodiscard]] bool isValid() const {
            return (
              statusCode > 0
            );
        }
    };
}