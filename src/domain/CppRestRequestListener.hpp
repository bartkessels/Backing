#pragma once

#include <cpprest/http_listener.h>
#include <memory>

#include "domain/exception/InvalidRequestException.hpp"
#include "domain/exception/InvalidResponseException.hpp"
#include "domain/exception/ListenerAlreadyClosedException.hpp"
#include "domain/exception/ListenerAlreadyStartedException.hpp"
#include "domain/exception/UnableToCloseConnectionException.hpp"
#include "domain/exception/UnableToStartConnectionException.hpp"
#include "domain/Logger.hpp"
#include "domain/RequestListener.hpp"

using namespace web::http::experimental::listener;

namespace backing::domain
{
    class CppRestRequestListener: public RequestListener
    {
    public:
        explicit CppRestRequestListener(const std::shared_ptr<Logger>& logger);
        ~CppRestRequestListener() override = default;

        void startListening() override;
        void stopListening() override;

    private:
        std::unique_ptr<http_listener> listener;
    };
}