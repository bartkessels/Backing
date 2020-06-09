#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct InvalidResponseException: public std::exception
    {
    public:
        explicit InvalidResponseException():
                message("The response contains one or more invalid fields") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}