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
        ~ListenerFactory() = default;

        std::shared_ptr<Listener> getListener();
    };
}