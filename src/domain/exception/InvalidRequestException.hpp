#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct InvalidRequestException: public std::exception
    {
    public:
        explicit InvalidRequestException():
                message("The request contains one or more invalid fields") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}