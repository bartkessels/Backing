#include <catch2/catch.hpp>

#include "domain/exception/ListenerAlreadyStartedException.hpp"

#include <iostream>

using namespace backing::domain;

TEST_CASE("ListenerAlreadyStartedException")
{
    SECTION("what contains both the method and the resource of the request")
    {
        // Arrange
        const auto& method = "GET";
        const auto& resource = "/error_message";

        try {
            throw exception::ListenerAlreadyStartedException(method, resource);
        } catch(exception::ListenerAlreadyStartedException& ex) {
            REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(method));
            REQUIRE_THAT(ex.what(), Catch::Matchers::Contains(resource));
        }
    }
}