#pragma once

#include <boost/format.hpp>
#include <string>
#include <memory>

#include "domain/Logger.hpp"
#include "domain/Request.hpp"
#include "domain/Response.hpp"

namespace backing::domain
{
    struct RequestListener
    {
    public:
        explicit RequestListener(const std::shared_ptr<Logger>& logger);
        virtual ~RequestListener() = default;

        RequestListener& listenFor(const std::shared_ptr<Request>& request);
        RequestListener& respondWith(const std::shared_ptr<Response>& response);

        virtual void startListening() = 0;
        virtual void stopListening() = 0;

    protected:
        void logConnection();
        void logConnectionOpened();
        void logConnectionClosed();

        std::shared_ptr<Logger> logger;
        std::shared_ptr<Request> request;
        std::shared_ptr<Response> response;
    };
}