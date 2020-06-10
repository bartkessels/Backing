#include <catch2/catch.hpp>

#include "domain/exception/ListenerAlreadyStartedException.hpp"

using namespace backing::domain;

TEST_CASE("what returns a message with the uri", "[ListenerAlreadyStartedException]")
{
    // Arrange
    const auto& uri = "http://localhost:5000/test";

    // Act & Assert
    try {
        throw exception::ListenerAlreadyStartedException(uri);
    } catch(exception::ListenerAlreadyStartedException& ex) {
        REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(uri));
    }
}
