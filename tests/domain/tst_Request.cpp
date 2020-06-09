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

    SECTION("validate returns true when method and https uri are valid")
    {
        // Arrange
        const std::string& method = "GET";
        const std::string& baseUri = "https://127.0.0.1";
        const std::string& resource = "/";
        const auto& request = std::make_unique<Request>();

        request->method = method;
        request->baseUri = baseUri;
        request->resource = resource;

        // Act
        const bool result = request->validate();

        // Assert
        REQUIRE(result);
    }

    SECTION("validate returns true when method and http uri are valid")
    {
        // Arrange
        const std::string& method = "GET";
        const std::string& baseUri = "http://127.0.0.1";
        const std::string& resource = "/";
        const auto& request = std::make_unique<Request>();

        request->method = method;
        request->baseUri = baseUri;
        request->resource = resource;

        // Act
        const bool result = request->validate();

        // Assert
        REQUIRE(result);
    }

    SECTION("validate returns true when uri doesnt contain a resource")
    {
        // Arrange
        const std::string& method = "GET";
        const std::string& baseUri = "http://127.0.0.1";
        const std::string& resource = "";
        const auto& request = std::make_unique<Request>();

        request->method = method;
        request->baseUri = baseUri;
        request->resource = resource;

        // Act
        const bool result = request->validate();

        // Assert
        REQUIRE(result);
    }

    SECTION("validate returns false when uri is missing the scheme")
    {
        // Arrange
        const std::string& method = "GET";
        const std::string& baseUri = "//127.0.0.1";
        const std::string& resource = "";
        const auto& request = std::make_unique<Request>();

        request->method = method;
        request->baseUri = baseUri;
        request->resource = resource;

        // Act
        const bool result = request->validate();

        // Assert
        REQUIRE_FALSE(result);
    }

    SECTION("validate returns false when uri is missing the server")
    {
        // Arrange
        const std::string& method = "GET";
        const std::string& baseUri = "";
        const std::string& resource = "/";
        const auto& request = std::make_unique<Request>();

        request->method = method;
        request->baseUri = baseUri;
        request->resource = resource;

        // Act
        const bool result = request->validate();

        // Assert
        REQUIRE_FALSE(result);
    }

    SECTION("validate returns false when method is invalid and uri is valid")
    {
        // Arrange
        const std::string& method = "";
        const std::string& baseUri = "http://127.0.0.1";
        const std::string& resource = "/";
        const auto& request = std::make_unique<Request>();

        request->method = method;
        request->baseUri = baseUri;
        request->resource = resource;

        // Act
        const bool result = request->validate();

        // Assert
        REQUIRE_FALSE(result);
    }
}