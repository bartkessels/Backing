#include <catch2/catch.hpp>

#include "domain/exception/MethodNotRegisteredException.hpp"

using namespace backing::domain;

TEST_CASE("what returns a message with the unregistered method", "[MethodNotRegisteredException]")
{
    // Arrange
    const auto& unregisteredMethod = "DELETE";

    // Act & Assert
    try {
        throw exception::MethodNotRegisteredException(unregisteredMethod);
    } catch(exception::MethodNotRegisteredException& ex) {
        REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(unregisteredMethod));
    }
}
