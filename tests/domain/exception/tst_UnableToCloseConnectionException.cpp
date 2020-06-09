#include <catch2/catch.hpp>

#include "domain/exception/UnableToCloseConnectionException.hpp"

using namespace backing::domain;

TEST_CASE("UnableToCloseConnectionException")
{
    SECTION("what contains both the method and the resource of the request")
    {
        // Arrange
        const auto& method = "GET";
        const auto& resource = "/error_message";

        try {
            throw exception::UnableToCloseConnectionException(method, resource);
        } catch(exception::UnableToCloseConnectionException& ex) {
            REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(method));
            REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(resource));
        }
    }
}