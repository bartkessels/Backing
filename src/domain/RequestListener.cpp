#include "domain/RequestListener.hpp"

using namespace backing::domain;

RequestListener::RequestListener(const std::shared_ptr<Logger>& logger):
    logger(logger)
{

}


RequestListener& RequestListener::listenFor(const std::shared_ptr<Request>& request)
{
    this->request = request;

    return *this;
}

RequestListener& RequestListener::respondWith(const std::shared_ptr<Response>& response)
{
    this->response = response;

    return *this;
}

void RequestListener::logConnection()
{
    auto logMessageTemplate = boost::format("%1% %2% → %3%") % request->method % request->resource % response->statusCode;

    logger->log(logMessageTemplate.str());
}

void RequestListener::logConnectionOpened()
{
    auto logMessageTemplate = boost::format("Listener on %1% %2% started") % request->method % request->resource;

    logger->log(logMessageTemplate.str());
}

void RequestListener::logConnectionClosed()
{
    auto logMessageTemplate = boost::format("Listener on %1% %2% stopped") % request->method % request->resource;

    logger->log(logMessageTemplate.str());
}