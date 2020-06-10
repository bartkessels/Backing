#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct MethodNotRegisteredException: public std::exception
    {
    public:
        explicit MethodNotRegisteredException(const std::string& method):
                message("Method '" + method + "' not registered") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}