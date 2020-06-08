#include "gui/widget/RequestListenerWidget/RequestListenerWidget.hpp"
#include "./ui_RequestListenerWidget.h"

using namespace backing::gui::widget;

RequestListenerWidget::RequestListenerWidget(std::shared_ptr<domain::RequestListener> listener, QWidget* parent):
    QWidget(parent),
    ui(new Ui::RequestListenerWidget()),
    listener(std::move(listener))
{
    ui->setupUi(this);
}

RequestListenerWidget::~RequestListenerWidget()
{
    delete ui;
}

void RequestListenerWidget::startListening(const std::string& method, const std::string& uri)
{
    const auto& request = std::make_shared<domain::Request>();
    const auto& response = this->buildResponse();
    auto resource = ui->textResource->text().toStdString();

    request->method = method;
    request->baseUri = uri;
    request->resource = resource;

    listener->listenFor(request)
        .respondWith(response)
        .startListening();
}

void RequestListenerWidget::stopListening()
{
    listener->stopListening();
}

std::shared_ptr<backing::domain::Response> RequestListenerWidget::buildResponse()
{
    auto statusCode = ui->textStatusCode->text().toStdString();
    auto contentType = ui->textContentType->text().toStdString();
    auto body = ui->textBody->document()->toPlainText().toStdString();
    const auto& response = std::make_shared<backing::domain::Response>();

    response->statusCode = std::stoi(statusCode);
    response->contentType = contentType;
    response->body = body;

    return response;
}

