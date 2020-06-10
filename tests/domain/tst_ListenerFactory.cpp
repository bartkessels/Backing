#include <catch2/catch.hpp>
#include <memory>

#include "domain/CppRestRequestListener.hpp"
#include "domain/ListenerFactory.hpp"
#include "domain/Logger.hpp"

using namespace backing::domain;

class MockLogger: public Logger
{
public:
    void log(std::string message) override {}
};

TEST_CASE("getListener returns a shared ptr with an instance of CppRestRequestListener", "[ListenerFactory]")
{
    // Arrange
    const auto& mockedLogger = std::make_shared<MockLogger>();

    const auto& sut = std::make_unique<ListenerFactory>(mockedLogger);

    // Act
    const auto& result = sut->getListener();

    // Assert
    REQUIRE(dynamic_cast<CppRestRequestListener*>(result.get()));
}