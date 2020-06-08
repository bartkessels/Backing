#pragma once

#include <cpprest/http_listener.h>
#include <memory>

#include "domain/exception/ListenerAlreadyClosedException.hpp"
#include "domain/exception/ListenerAlreadyStartedException.hpp"
#include "domain/Logger.hpp"
#include "domain/RequestListener.hpp"

using namespace web::http::experimental::listener;

namespace backing::domain
{
    class CppRestRequestListener: public RequestListener
    {
    public:
        explicit CppRestRequestListener(const std::shared_ptr<Logger>& logger);
        ~CppRestRequestListener() override;

        void startListening() override;
        void stopListening() override;

    private:
        http_listener* listener = nullptr;
    };
}