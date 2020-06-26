#include "domain/CppRestRequestListener.hpp"

using namespace backing::domain;

bool CppRestRequestListener::startListener(const std::string &uri)
{
    listener = std::make_unique<http_listener>(uri);
    listener->support([=](const web::http::http_request& request) {
        const std::string requestMethod = utility::conversions::to_utf8string(request.method());
        const std::string requestResource = utility::conversions::to_utf8string(request.request_uri().resource().to_string());

        this->log(requestMethod + " request received on " + requestResource);

        try {
            std::shared_ptr<Response> response = getResponse(requestMethod);
            const utility::string_t responseBody = utility::conversions::to_string_t(response->body);

            web::http::http_response httpResponse(response->statusCode);
            httpResponse.set_body(responseBody);

            for (const auto& [header, value]: response->headers) {
                const utility::string_t responseHeader = utility::conversions::to_string_t(header);
                const utility::string_t responseHeaderValue = utility::conversions::to_string_t(value);

                httpResponse.headers().add(responseHeader, responseHeaderValue);
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