#pragma once

#include <boost/format.hpp>
#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct ListenerAlreadyClosedException: public std::exception
    {
    public:
        explicit ListenerAlreadyClosedException(const std::string& method, const std::string& uri):
                message("Listener on " + uri + " already closed for " + method) {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}