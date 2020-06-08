#pragma once

#include <string>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseWidget; }
QT_END_NAMESPACE

namespace backing::gui::widget
{
    class ResponseWidget: public QWidget
    {
    public:
        explicit ResponseWidget(std::string  methodName, QWidget* parent = nullptr);
        ~ResponseWidget() override;

    private:
        Ui::ResponseWidget* ui;
        std::string methodName;
    };
}