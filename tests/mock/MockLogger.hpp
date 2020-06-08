#pragma once

#include "domain/Logger.hpp"

namespace backing::tests::mock
{
    class MockLogger: public domain::Logger
    {
    public:
        MockLogger() = default;
        ~MockLogger() override = default;

        void log(std::string) override {}
    };
}