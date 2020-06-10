#pragma once

#include <memory>
#include <string>
#include <utility>

#include "domain/CppRestRequestListener.hpp"
#include "domain/Listener.hpp"
#include "domain/Logger.hpp"

namespace backing::domain
{
    class ListenerFactory
    {
    public:
        explicit ListenerFactory(std::shared_ptr<Logger> logger);
        ~ListenerFactory() = default;

        std::shared_ptr<Listener> getListener();

    private:
        std::shared_ptr<Logger> logger;
    };
}