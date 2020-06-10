#include "domain/Listener.hpp"

using namespace backing::domain;

void Listener::registerMethod(const std::string& name, const std::shared_ptr<Response>& response)
{
    this->methods.insert_or_assign(name, response);
}

void Listener::unregisterMethod(const std::string& name)
{
    const auto& it = this->methods.find(name);

    if (it != this->methods.end()) {
        this->methods.erase(it);
    }
}

void Listener::start(const std::string& uri)
{
    if (!validateUri(uri)) throw exception::InvalidUriException(uri);
    if (listenerStarted) throw exception::ListenerAlreadyStartedException(uri);

    listenerStarted = startListener(uri);
}

void Listener::stop()
{
    if (!listenerStarted) throw exception::ListenerNotStartedException();

    stopListener();
    listenerStarted = false;
}

std::shared_ptr<Response> Listener::getResponse(const std::string& method)
{
    const auto& it = this->methods.find(method);

    if (it == this->methods.end()) {
        throw exception::MethodNotRegisteredException(method);
    }

    return it->second;
}

bool Listener::validateUri(const std::string& uri)
{
    return std::regex_match(uri, std::regex("^(?:http://)?([^/]+)(?:/?.*/?)/(.*)$"));
}