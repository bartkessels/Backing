#pragma once

#include <memory>
#include <QWidget>
#include <utility>

#include "domain/Request.hpp"
#include "domain/RequestListener.hpp"
#include "domain/Response.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RequestListenerWidget; }
QT_END_NAMESPACE

namespace backing::gui::widget
{
    class RequestListenerWidget: public QWidget
    {
        Q_OBJECT

    public:
        explicit RequestListenerWidget(std::shared_ptr<domain::RequestListener> listener, QWidget* parent = nullptr);
        ~RequestListenerWidget() override;

        void startListening(const std::string& method, const std::string& uri);
        void stopListening();

    private:
        std::shared_ptr<domain::Response> buildResponse();

        Ui::RequestListenerWidget* ui;
        std::shared_ptr<domain::RequestListener> listener;
    };
}