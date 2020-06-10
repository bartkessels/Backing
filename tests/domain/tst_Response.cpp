#include <catch2/catch.hpp>
#include <memory>

#include "domain/Response.hpp"

using namespace backing::domain;

TEST_CASE("isValid returns true when statusCode is larger than 0", "[Response]")
{
    // Arrange
    const int statusCode = 200;
    const std::string& body = "";
    const auto& response = std::make_unique<Response>();

    response->statusCode = statusCode;
    response->body = body;

    // Act
    const bool result = response->isValid();

    // Assert
    REQUIRE(result);
}

TEST_CASE("isValid returns false when statusCode is equal to 0", "[Response]")
{
    // Arrange
    const int statusCode = 0;
    const std::string& body = "";
    const auto& response = std::make_unique<Response>();

    response->statusCode = statusCode;
    response->body = body;

    // Act
    const bool result = response->isValid();

    // Assert
    REQUIRE_FALSE(result);
}

TEST_CASE("isValid returns false when statusCode is smaller than 0", "[Response]")
{
    // Arrange
    const int statusCode = -2;
    const std::string& body = "";
    const auto& response = std::make_unique<Response>();

    response->statusCode = statusCode;
    response->body = body;

    // Act
    const bool result = response->isValid();

    // Assert
    REQUIRE_FALSE(result);
}