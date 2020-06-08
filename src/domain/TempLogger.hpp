#pragma once

#include <iostream>

#include "domain/Logger.hpp"

namespace backing::domain
{
    class TempLogger: public Logger
    {
    public:
        TempLogger() = default;
        ~TempLogger() override = default;

        void log(std::string message) override {
            std::cout << message << std::endl;
        }
    };
}