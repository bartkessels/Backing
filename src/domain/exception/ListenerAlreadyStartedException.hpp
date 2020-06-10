#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct ListenerAlreadyStartedException: public std::exception
    {
    public:
        explicit ListenerAlreadyStartedException(const std::string& uri):
            message("Listener for '" + uri + "' already started") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}