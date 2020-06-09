#include "domain/CppRestRequestListener.hpp"

using namespace backing::domain;

CppRestRequestListener::CppRestRequestListener(const std::shared_ptr<Logger>& logger):
    RequestListener(logger)
{

}

void CppRestRequestListener::startListening()
{
    if (!response->validate()) throw exception::InvalidResponseException();
    if (!request->validate()) throw exception::InvalidRequestException();
    if (listener != nullptr) throw exception::ListenerAlreadyStartedException(request->method, request->resource);

    listener = std::make_unique<http_listener>(request->completeUri());
    listener->support(request->method, [=](const web::http::http_request& request) {
        web::http::http_response httpResponse(response->statusCode);
        httpResponse.headers().set_content_type(response->contentType);
        httpResponse.set_body(response->body);

        request.reply(httpResponse);
        this->logConnection();
    });

    listener->open().then([=](const pplx::task<void>& task) {
        try {
            task.get();
            this->logConnectionOpened();
        } catch(std::exception& e) {
            listener.reset();
            throw exception::UnableToStartConnectionException(request->method, request->resource);
        }
    }).wait();
}

void CppRestRequestListener::stopListening()
{
    if (listener == nullptr) {
        throw exception::ListenerAlreadyClosedException(request->method, request->resource);
    }

    listener->close().then([=](const pplx::task<void>& task) {
        try {
            task.get();
            this->logConnectionClosed();
        } catch(std::exception& e) {
            listener.reset();
            throw exception::UnableToCloseConnectionException(request->method, request->resource);
        }
    }).wait();

    listener.reset();
}