#include <catch2/catch.hpp>
#include <memory>

#include "domain/Request.hpp"

using namespace backing::domain;

TEST_CASE("Request")
{
    SECTION("completeUri concatenates the baseUri and the resource")
    {
        // Arrange
        const std::string& baseUri = "http://localhost:5000";
        const std::string& resource = "/res";
        const std::string& expectedUri = baseUri + resource;
        const auto& request = std::make_unique<Request>();

        // Act
        request->baseUri = baseUri;
        request->resource = resource;

        // Assert
        REQUIRE(expectedUri == request->completeUri());
    }
}