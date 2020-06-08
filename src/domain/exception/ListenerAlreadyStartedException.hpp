#pragma once

#include <boost/format.hpp>
#include <exception>
#include <string>

namespace backing::domain::exception
{
    struct ListenerAlreadyStartedException: public std::exception
    {
    public:
        explicit ListenerAlreadyStartedException(const std::string& method, const std::string& uri):
                message("Listener on " + uri + " already started for " + method) {}

        [[nodiscard]] const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };
}