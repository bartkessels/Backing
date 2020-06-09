#pragma once

#include <regex>
#include <string>

namespace backing::domain
{
    struct Request
    {
    public:
        std::string method;
        std::string baseUri;
        std::string resource;

        [[nodiscard]] std::string completeUri() const {
            return baseUri + resource;
        }

        [[nodiscard]] bool validate() const {
            return (
                !method.empty() &&
                validateUri()
            );
        }

    private:
        [[nodiscard]] bool validateUri() const {
            return std::regex_match(completeUri(), std::regex("^(?:http://)?([^/]+)(?:/?.*/?)/(.*)$"));
        }
    };
}