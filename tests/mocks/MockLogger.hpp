#pragma once

#include <string>

#include "domain/Logger.hpp"

namespace backing::tests::mocks
{
    class MockLogger: public domain::Logger
    {
    public:
        ~MockLogger() override = default;

        void log(std::string) override {}
    };
}