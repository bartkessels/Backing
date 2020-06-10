#include "domain/CppRestRequestListener.hpp"

using namespace backing::domain;

bool CppRestRequestListener::startListener(const std::string &uri)
{
    listener = std::make_unique<http_listener>(uri);
    listener->support([=](const web::http::http_request& request) {
        this->log(request.method() + " request received on " + request.request_uri().resource().to_string());

        try {
            std::shared_ptr<Response> response = getResponse(request.method());
            web::http::http_response httpResponse(response->statusCode);
            httpResponse.set_body(response->body);

            for (const auto& [header, value]: response->headers) {
                httpResponse.headers().add(header, value);
            }

            request.reply(httpResponse);
        } catch(exception::MethodNotRegisteredException&) {
            request.reply(web::http::status_codes::MethodNotAllowed);
        }
    });

    return listener->open().wait() == pplx::task_status::completed;
}

void CppRestRequestListener::stopListener()
{
    listener->close().wait();
    listener.reset();
}