#include <catch2/catch.hpp>
#include <memory>

#include "domain/Response.hpp"

using namespace backing::domain;

TEST_CASE("isValid returns true when statusCode is larger than 0", "[Response]")
{
    // Arrange
    const auto& response = std::make_unique<Response>();

    response->statusCode = 200;
    response->body = "";

    // Act
    const bool result = response->isValid();

    // Assert
    REQUIRE(result);
}

TEST_CASE("isValid returns false when statusCode is equal to 0", "[Response]")
{
    // Arrange
    const auto& response = std::make_unique<Response>();

    response->statusCode = 0;
    response->body = "";

    // Act
    const bool result = response->isValid();

    // Assert
    REQUIRE_FALSE(result);
}

TEST_CASE("isValid returns false when statusCode is smaller than 0", "[Response]")
{
    // Arrange
    const auto& response = std::make_unique<Response>();

    response->statusCode = -1;
    response->body = "";

    // Act
    const bool result = response->isValid();

    // Assert
    REQUIRE_FALSE(result);
}