#include <catch2/catch.hpp>

#include "domain/exception/InvalidUriException.hpp"

using namespace backing::domain;

TEST_CASE("what returns a message with the invalid uri", "[InvalidUriException]")
{
    // Arrange
    const auto& uri = "invalid_uri.host";

    // Act & Assert
    try {
        throw exception::InvalidUriException(uri);
    } catch(exception::InvalidUriException& ex) {
        REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(uri));
    }
}
