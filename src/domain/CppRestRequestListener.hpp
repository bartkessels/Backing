#pragma once

#include <cpprest/http_listener.h>
#include <memory>
#include <string>

#include "domain/Listener.hpp"

using namespace web::http::experimental::listener;

namespace backing::domain
{
    class CppRestRequestListener: public Listener
    {
    public:
        explicit CppRestRequestListener() = default;
        ~CppRestRequestListener() override = default;

        bool startListener(const std::string& uri) override;
        void stopListener() override;

    private:
        std::unique_ptr<http_listener> listener;
    };
}
