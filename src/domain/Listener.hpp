#pragma once

#include <map>
#include <memory>
#include <regex>
#include <string>

#include "domain/exception/InvalidUriException.hpp"
#include "domain/exception/ListenerAlreadyStartedException.hpp"
#include "domain/exception/ListenerNotStartedException.hpp"
#include "domain/exception/MethodNotRegisteredException.hpp"
#include "domain/Logger.hpp"
#include "domain/Response.hpp"

namespace backing::domain
{
    class Listener
    {
    public:
        virtual ~Listener() = default;
        void registerMethod(const std::string& name, const std::shared_ptr<Response>& response);
        void unregisterMethod(const std::string& name);

        void setLogger(const std::shared_ptr<Logger>& logger);
        void start(const std::string& uri);
        void stop();

    protected:
        bool listenerStarted = false;
        std::shared_ptr<Logger> logger = nullptr;
        std::map<std::string, std::shared_ptr<Response>> methods;

        std::shared_ptr<Response> getResponse(const std::string& method);
        void log(const std::string& message);
        virtual bool startListener(const std::string& uri) = 0;
        virtual void stopListener() = 0;

    private:
        static bool validateUri(const std::string& uri);
    };
}