#include "domain/CppRestRequestListener.hpp"

using namespace backing::domain;

CppRestRequestListener::CppRestRequestListener(const std::shared_ptr<Logger>& logger):
    RequestListener(logger)
{

}

CppRestRequestListener::~CppRestRequestListener()
{
    if (listener != nullptr) {
        listener->close().wait();
        delete listener;
    }
}

void CppRestRequestListener::startListening()
{
    if (!response->validate()) throw exception::InvalidResponseException();
    if (!request->validate()) throw exception::InvalidRequestException();
    if (listener != nullptr) throw exception::ListenerAlreadyStartedException(request->method, request->resource);

    listener = new http_listener(request->completeUri());
    listener->support(request->method, [=](const web::http::http_request& request) {
        web::http::http_response httpResponse(response->statusCode);
        httpResponse.headers().add("Content-Type", response->contentType);
        httpResponse.set_body(response->body);

        request.reply(httpResponse);
        this->logConnection();
    });

    listener->open().wait();
    this->logConnectionOpened();
}

void CppRestRequestListener::stopListening()
{
    if (listener == nullptr) {
        throw exception::ListenerAlreadyClosedException(request->method, request->resource);
    }

    listener->close().wait();

    this->logConnectionClosed();
    delete listener;
    listener = nullptr;
}