#include <catch2/catch.hpp>
#include <cpprest/http_client.h>
#include <functional>
#include <memory>
#include <utility>

#include "domain/CppRestRequestListener.hpp"
#include "domain/Response.hpp"

using namespace backing::domain;

void sendRequest(const std::string& method, const std::string& uri, std::function<void(web::http::http_response)> callback) {
    bool requestSent = false;

    const utility::string_t requestMethod = utility::conversions::to_string_t(method);
    const utility::string_t requestUri = utility::conversions::to_string_t(uri);

    web::http::client::http_client client(requestUri);
    web::http::http_request request;

    request.set_method(requestMethod);
    client.request(request).then([&](web::http::http_response response) {
        callback(std::move(response));

        requestSent = true;
    });

    while (!requestSent) {}
}

TEST_CASE("listener returns method not allowed when trying to access an unregistered method")
{
    // Arrange
    const auto& method = "GET";
    const auto& uri = "http://localhost:1384";

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->start(uri);

    // Act & Assert
    sendRequest(method, uri, [=](const web::http::http_response& actualResponse) {
        REQUIRE(actualResponse.status_code() == web::http::status_codes::MethodNotAllowed);
    });
}

TEST_CASE("listener returns response with given status code")
{
    // Arrange
    const auto& method = "GET";
    const auto& uri = "http://localhost:1384";
    const auto& response = std::make_shared<Response>();

    response->statusCode = 201;

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->registerMethod(method, response);
    sut->startListener(uri);

    // Act & Assert
    sendRequest(method, uri, [=](const web::http::http_response& actualResponse) {
        REQUIRE(actualResponse.status_code() == response->statusCode);
    });
}

TEST_CASE("listener returns response with given headers")
{
    // Arrange
    const auto& method = "GET";
    const auto& uri = "http://localhost:1384";
    const auto& customHeader = "Custom-Header";
    const auto& customHeaderValue = "Custom header value";
    const auto& response = std::make_shared<Response>();

    response->headers.insert({customHeader, customHeaderValue});

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->registerMethod(method, response);
    sut->start(uri);

    // Act & Assert
    sendRequest(method, uri, [=](const web::http::http_response& actualResponse) {
        const std::string responseHeaderValue = utility::conversions::to_utf8string(actualResponse.headers().find(customHeader)->second);

        REQUIRE(responseHeaderValue == customHeaderValue);
    });
}

TEST_CASE("listener returns response with given body")
{
    // Arrange
    const auto& method = "GET";
    const auto& uri = "http://localhost:1384";
    const auto& response = std::make_shared<Response>();

    response->body = "My own body";

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->registerMethod(method, response);
    sut->start(uri);

    // Act & Assert
    sendRequest(method, uri, [=](const web::http::http_response& actualResponse) {
        const std::string responseBody = utility::conversions::to_utf8string(actualResponse.extract_string().get());

        REQUIRE(responseBody == response->body);
    });
}

TEST_CASE("listener returns not found for other resource than given in the uri")
{
    // Arrange
    const auto& method = "GET";
    const auto& uri = "http://localhost:1384/specific-resource";
    const auto& uriForDifferentResource = "http://localhost:1384/another-resource";
    const auto& response = std::make_shared<Response>();

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->registerMethod(method, response);
    sut->start(uri);

    // Act & Assert
    sendRequest(method, uriForDifferentResource, [=](const web::http::http_response& actualResponse) {
        REQUIRE(actualResponse.status_code() == web::http::status_codes::NotFound);
    });
}

TEST_CASE("listener returns different responses for different methods")
{
    // Arrange
    const auto& firstMethod = "GET";
    const auto& secondMethod = "POST";
    const auto& uri = "http://localhost:1384/";
    const auto& firstResponse = std::make_shared<Response>();
    const auto& secondResponse = std::make_shared<Response>();

    firstResponse->statusCode = 200;
    secondResponse->statusCode = 201;

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->registerMethod(firstMethod, firstResponse);
    sut->registerMethod(secondMethod, secondResponse);

    sut->start(uri);

    // Act & Assert
    sendRequest(firstMethod, uri, [=](const web::http::http_response& actualResponse) {
       REQUIRE(actualResponse.status_code() == firstResponse->statusCode);
    });

    sendRequest(secondMethod, uri, [=](const web::http::http_response& actualResponse) {
        REQUIRE(actualResponse.status_code() == secondResponse->statusCode);
    });
}

TEST_CASE("listener keeps listening to requests after a starting, stopping and starting again")
{
    // Arrange
    const auto& method = "GET";
    const auto& uri = "http://localhost:1384";
    const auto& response = std::make_shared<Response>();

    response->body = "My own body";

    const auto& sut = std::make_unique<CppRestRequestListener>();

    sut->registerMethod(method, response);
    sut->start(uri);
    sut->stop();
    sut->start(uri);

    // Act & Assert
    sendRequest(method, uri, [=](const web::http::http_response& actualResponse) {
        const std::string responseBody = utility::conversions::to_utf8string(actualResponse.extract_string().get());

        REQUIRE(responseBody == response->body);
    });
}
