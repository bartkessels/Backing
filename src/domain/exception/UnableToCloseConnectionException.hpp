#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct UnableToCloseConnectionException: public std::exception
    {
    public:
        explicit UnableToCloseConnectionException(const std::string& method, const std::string& uri):
                message("The connection for " + uri + " on " + method + " could not be closed") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}