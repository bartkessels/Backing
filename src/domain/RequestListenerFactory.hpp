#pragma once

#include <string>
#include <memory>
#include <utility>

#include "domain/CppRestRequestListener.hpp"
#include "domain/Logger.hpp"
#include "domain/RequestListener.hpp"

namespace backing::domain
{
    class RequestListenerFactory
    {
    public:
        explicit RequestListenerFactory(std::shared_ptr<Logger> logger);
        ~RequestListenerFactory() = default;

        std::shared_ptr<RequestListener> getRequestListener();

    private:
        std::shared_ptr<Logger> logger;
    };
}