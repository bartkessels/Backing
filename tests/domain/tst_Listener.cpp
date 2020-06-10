#include <catch2/catch.hpp>
#include <map>
#include <memory>
#include <string>

#include "domain/exception/InvalidUriException.hpp"
#include "domain/exception/ListenerAlreadyStartedException.hpp"
#include "domain/exception/ListenerNotStartedException.hpp"
#include "domain/Listener.hpp"
#include "domain/Response.hpp"
#include "domain/Logger.hpp"

using namespace backing::domain;

class MockLogger: public Logger
{
public:
    std::string logMessage;

    void log(const std::string& message) override {
        this->logMessage = message;
    }
};

class MockListener: public Listener
{
public:
    explicit MockListener(const bool startListenerResult):
        startListenerResult(startListenerResult) {}

    std::shared_ptr<Response> sendRequest(const std::string& method) { return getResponse(method); }
    std::map<std::string, std::shared_ptr<Response>> getMethods() { return methods; }
    void writeToLogger(const std::string& message) { this->log(message); }

protected:
    bool startListener(const std::string& uri) override { return startListenerResult; }
    void stopListener() override { }

private:
    bool startListenerResult;
};

TEST_CASE("start throws InvalidUriException for invalid uri")
{
    // Arrange
    const bool startListenerResult = true;

    const auto& invalidUri = "not-valid.uri";
    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act & Assert
    REQUIRE_THROWS_AS(sut->start(invalidUri), exception::InvalidUriException);
}

TEST_CASE("start continues with a valid uri")
{
    // Arrange
    const bool startListenerResult = true;

    const auto& validUri = "http://localhost:5000";
    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act & Assert
    REQUIRE_NOTHROW(sut->start(validUri));
}

TEST_CASE("start throws ListenerAlreadyStartedException when the listener is already started")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& uri = "http://localhost:5000/";
    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    sut->start(uri);

    // Act & Assert
    REQUIRE_THROWS_AS(sut->start(uri), exception::ListenerAlreadyStartedException);
}

TEST_CASE("stop throws ListenerNotStartedException when the listener is never started")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act & Assert
    REQUIRE_THROWS_AS(sut->stop(), exception::ListenerNotStartedException);
}

TEST_CASE("stop throws ListenerNotStartedException on the second stop call when the listener is started and then twice stopped")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& uri = "http://localhost:5000/";
    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    sut->start(uri);
    sut->stop();

    // Act & Assert
    REQUIRE_THROWS_AS(sut->stop(), exception::ListenerNotStartedException);
}

TEST_CASE("register adds the method to the map")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& method = "GET";
    const auto& response = std::make_shared<Response>();

    response->statusCode = 201;

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act
    sut->registerMethod(method, response);

    // Assert
    const auto& it = sut->getMethods().find(method);

    REQUIRE(it->first == method);
    REQUIRE(it->second->statusCode == response->statusCode);
}

TEST_CASE("register overwrites a method with the second given method")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& method = "GET";
    const auto& firstResponse = std::make_shared<Response>();
    const auto& secondResponse = std::make_shared<Response>();

    firstResponse->statusCode = 201;
    secondResponse->statusCode = 500;

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act
    sut->registerMethod(method, firstResponse);
    sut->registerMethod(method, secondResponse);

    // Assert
    const auto& it = sut->getMethods().find(method);

    REQUIRE(it->second->statusCode == secondResponse->statusCode);
}

TEST_CASE("unregister removes the method")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& method = "GET";
    const auto& response = std::make_shared<Response>();

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    sut->registerMethod(method, response);

    // Act
    sut->unregisterMethod(method);

    // Assert
    REQUIRE(sut->getMethods().empty());
}

TEST_CASE("unregister does nothing when trying to remove a method that wasn't registered")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& unregisteredMethod = "GET";

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act
    sut->unregisterMethod(unregisteredMethod);

    // Assert
    REQUIRE(sut->getMethods().empty());
}

TEST_CASE("getResponse returns response object for the registered method")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& method = "GET";
    const auto& response = std::make_shared<Response>();

    response->statusCode = 201;

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    sut->registerMethod(method, response);

    // Act
    const auto& result = sut->sendRequest(method);

    // Assert
    REQUIRE(result->statusCode == response->statusCode);
}

TEST_CASE("getResponse throws MethodNotRegisteredException when trying to get the response for an unregistered method")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& method = "GET";

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act & Assert
    REQUIRE_THROWS_AS(sut->sendRequest(method), exception::MethodNotRegisteredException);
}

TEST_CASE("log sends the message to the logger when one is set")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& mockedLogger = std::make_shared<MockLogger>();
    const auto& logMessage = "This is my log";

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act
    sut->setLogger(mockedLogger);
    sut->writeToLogger(logMessage);

    // Arrange
    REQUIRE(mockedLogger->logMessage == logMessage);
}

TEST_CASE("log does nothing when no logger is set")
{
    // Arrange
    const bool startListenerResult = true;
    const auto& mockedLogger = new MockLogger();
    const auto& logMessage = "This is my log";

    const auto& sut = std::make_unique<MockListener>(startListenerResult);

    // Act & Assert
    REQUIRE_NOTHROW(sut->writeToLogger(logMessage));
}
