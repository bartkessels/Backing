#pragma once

#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct ListenerNotStartedException: public std::exception
    {
    public:
        explicit ListenerNotStartedException():
                message("Listener cannot be stopped 'cause it hasn't been started") {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}