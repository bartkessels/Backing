#include <catch2/catch.hpp>

#include "domain/exception/UnableToStartConnectionException.hpp"

using namespace backing::domain;

TEST_CASE("UnableToStartConnectionException")
{
    SECTION("what contains both the method and the resource of the request")
    {
        // Arrange
        const auto& method = "GET";
        const auto& resource = "/error_message";

        try {
            throw exception::UnableToStartConnectionException(method, resource);
        } catch(exception::UnableToStartConnectionException& ex) {
            REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(method));
            REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(resource));
        }
    }
}