#include <catch2/catch.hpp>
#include <memory>

#include "domain/RequestListenerFactory.hpp"

#include "mock/MockLogger.hpp"

using namespace backing::domain;
using namespace backing::tests;

TEST_CASE("RequestListenerFactory")
{
    // Before
    const auto& mockedLogger = std::make_shared<mock::MockLogger>();

    SECTION("getRequestListener returns a shared ptr with an instance of CppRestRequestListener")
    {
        // Arrange
        const auto& factory = std::make_unique<RequestListenerFactory>(mockedLogger);

        // Act
        const auto& result = factory->getRequestListener();

        // Assert
        REQUIRE(dynamic_cast<CppRestRequestListener*>(result.get()));
    }
}