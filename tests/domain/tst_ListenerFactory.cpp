#include <catch2/catch.hpp>
#include <memory>

#include "domain/CppRestRequestListener.hpp"
#include "domain/ListenerFactory.hpp"

using namespace backing::domain;

TEST_CASE("getListener returns a shared ptr with an instance of CppRestRequestListener", "[ListenerFactory]")
{
    // Arrange
    const auto& sut = std::make_unique<ListenerFactory>();

    // Act
    const auto& result = sut->getListener();

    // Assert
    REQUIRE(dynamic_cast<CppRestRequestListener*>(result.get()));
}