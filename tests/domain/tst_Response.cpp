#include <catch2/catch.hpp>
#include <memory>

#include "domain/Response.hpp"


using namespace backing::domain;

TEST_CASE("Response")
{
    SECTION("validate returns true for valid status code valid content-type and a body")
    {
        // Arrange
        const int statusCode = 200;
        const auto& contentType = "text/plain";
        const auto& body = "Hello world";
        const auto& response = std::make_unique<Response>();

        response->statusCode = statusCode;
        response->contentType = contentType;
        response->body = body;

        // Act
        const bool result = response->validate();

        // Assert
        REQUIRE(result);
    }

    SECTION("validate returns true when the body is empty")
    {
        // Arrange
        const int statusCode = 200;
        const auto& contentType = "text/plain";
        const auto& body = "";
        const auto& response = std::make_unique<Response>();

        response->statusCode = statusCode;
        response->contentType = contentType;
        response->body = body;

        // Act
        const bool result = response->validate();

        // Assert
        REQUIRE(result);
    }

    SECTION("validate returns false when the status code is less than 0")
    {
        // Arrange
        const int statusCode = -1;
        const auto& contentType = "text/plain";
        const auto& body = "Hello world";
        const auto& response = std::make_unique<Response>();

        response->statusCode = statusCode;
        response->contentType = contentType;
        response->body = body;

        // Act
        const bool result = response->validate();

        // Assert
        REQUIRE_FALSE(result);
    }

    SECTION("validate returns false when the status code is 0")
    {
        // Arrange
        const int statusCode = 0;
        const auto& contentType = "text/plain";
        const auto& body = "Hello world";
        const auto& response = std::make_unique<Response>();

        response->statusCode = statusCode;
        response->contentType = contentType;
        response->body = body;

        // Act
        const bool result = response->validate();

        // Assert
        REQUIRE_FALSE(result);
    }

    SECTION("validate returns false when the content type is empty")
    {
        // Arrange
        const int statusCode = 200;
        const auto& contentType = "";
        const auto& body = "Hello world";
        const auto& response = std::make_unique<Response>();

        response->statusCode = statusCode;
        response->contentType = contentType;
        response->body = body;

        // Act
        const bool result = response->validate();

        // Assert
        REQUIRE_FALSE(result);
    }
}