#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct UnableToStartConnectionException: public std::exception
    {
    public:
        explicit UnableToStartConnectionException(const std::string& method, const std::string& uri):
                message("The connection for " + uri + " on " + method + " could not be started") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}