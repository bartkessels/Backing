#include <catch2/catch.hpp>
#include <cpprest/http_client.h>
#include <functional>
#include <memory>
#include <utility>

#include "domain/exception/ListenerAlreadyClosedException.hpp"
#include "domain/exception/ListenerAlreadyStartedException.hpp"
#include "domain/CppRestRequestListener.hpp"

#include "mock/MockLogger.hpp"

using namespace backing::domain;
using namespace backing::tests;

void sendRequest(const std::string& method, const std::string& uri, std::function<void(web::http::http_response)> callback) {
    bool requestSent = false;

    web::http::client::http_client client(uri);
    web::http::http_request request;

    request.set_method(method);
    client.request(request).then([&](web::http::http_response response) {
        callback(std::move(response));

        requestSent = true;
    });

    while (!requestSent) {}
}

TEST_CASE("CppRestRequestListener")
{
    // Before
    const std::string& baseUri = "http://localhost:1384";
    const auto& mockedLogger = std::make_shared<mock::MockLogger>();

    const auto& sut = std::make_shared<CppRestRequestListener>(mockedLogger);

    SECTION("startListening throws ListenerAlreadyStartedException when called twice in a row")
    {
        // Arrange
        const auto& request = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        request->method = "GET";
        request->baseUri = baseUri;
        request->resource = "/";

        response->statusCode = 200;
        response->contentType = "text/plain";

        // Act
        sut->listenFor(request).respondWith(response);
        sut->startListening();

        // Assert
        CHECK_THROWS_AS(sut->startListening(), exception::ListenerAlreadyStartedException);
    }

    SECTION("stopListening throws ListenerAlreadyStoppedException when called twice")
    {
        // Arrange
        const auto& request = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        request->method = "GET";
        request->baseUri = baseUri;
        request->resource = "/";

        response->statusCode = 200;
        response->contentType = "text/plain";

        // Act
        sut->listenFor(request).respondWith(response);
        sut->startListening();
        sut->stopListening();

        // Assert
        CHECK_THROWS_AS(sut->stopListening(), exception::ListenerAlreadyClosedException);
    }

    SECTION("startListening returns the response for the exact resource")
    {
        // Arrange
        const auto& request = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        request->method = "GET";
        request->baseUri = baseUri;
        request->resource = "/test";

        response->statusCode = 201;
        response->contentType = "text/plain";
        response->body = "created";

        sut->listenFor(request).respondWith(response);
        sut->startListening();

        // Act & Assert
        sendRequest(request->method, request->completeUri(), [=](const web::http::http_response& actualResponse) {
            REQUIRE(response->body == actualResponse.extract_string().get());
            REQUIRE(response->contentType == actualResponse.headers().content_type());
            REQUIRE(response->statusCode == actualResponse.status_code());
        });
    }

    SECTION("startListening returns 404 for a non-existing resource")
    {
        // Arrange
        const auto& request = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        request->method = "GET";
        request->baseUri = baseUri;
        request->resource = "/test";

        response->statusCode = 201;
        response->contentType = "text/plain";
        response->body = "created";

        sut->listenFor(request).respondWith(response);

        // Act
        sut->startListening();

        // Assert
        sendRequest(request->method, request->baseUri + "/non-existing", [=](const web::http::http_response& actualResponse) {
            REQUIRE(web::http::status_codes::NotFound == actualResponse.status_code());
        });
    }

    SECTION("startListening does not respond to updated request without restart")
    {
        // Arrange
        const auto& oldRequest = std::make_shared<Request>();
        const auto& newRequest = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        oldRequest->method = "GET";
        oldRequest->baseUri = baseUri;
        oldRequest->resource = "/old";

        newRequest->method = "POST";
        newRequest->baseUri = baseUri;
        newRequest->resource = "/new";

        response->statusCode = 200;
        response->contentType = "text/plain";
        response->body = "ok";

        // Act
        sut->listenFor(oldRequest).respondWith(response);
        sut->startListening();
        sut->listenFor(newRequest);

        // Assert
        sendRequest(oldRequest->method, oldRequest->completeUri(), [=](const web::http::http_response& actualResponse) {
            REQUIRE(response->statusCode == actualResponse.status_code());
            REQUIRE(response->contentType == actualResponse.headers().content_type());
            REQUIRE(response->body == actualResponse.extract_string().get());
        });

        sendRequest(newRequest->method, newRequest->completeUri(), [=](const web::http::http_response& actualResponse) {
            REQUIRE(web::http::status_codes::NotFound == actualResponse.status_code());
        });
    }

    SECTION("startListening throws InvalidRequestException when trying to start with an invalid request")
    {
        // Arrange
        const auto& request = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        response->statusCode = 200;
        response->contentType = "text/plain";
        response->body = "Hello world";

        // Act
        sut->listenFor(request).respondWith(response);

        // Assert
        REQUIRE_THROWS_AS(sut->startListening(), exception::InvalidRequestException);
    }

    SECTION("startListening throws InvalidResponseException when trying to start with an invalid response")
    {
        // Arrange
        const auto& request = std::make_shared<Request>();
        const auto& response = std::make_shared<Response>();

        request->method = "GET";
        request->baseUri = "http://127.0.0.1:5000";
        request->resource = "/";

        // Act
        sut->listenFor(request).respondWith(response);

        // Assert
        REQUIRE_THROWS_AS(sut->startListening(), exception::InvalidResponseException);
    }

    SECTION("startListening throws ... when trying to start with an empty response")
    {

    }

    SECTION("startListening throws ... when trying to start twice on the same resource")
    {

    }
}