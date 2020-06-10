#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct InvalidUriException: public std::exception
    {
    public:
        explicit InvalidUriException(const std::string& uri):
            message("The uri '" + uri + "' is not a valid uri") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}