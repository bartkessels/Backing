#pragma once

#include <string>
#include <QString>
#include <QWidget>

#include "domain/Logger.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class LoggingWidget; }
QT_END_NAMESPACE

namespace backing::gui::widget
{
    class LoggingWidget: public QWidget, public domain::Logger
    {
    public:
        explicit LoggingWidget(QWidget* parent = nullptr);
        ~LoggingWidget() override;

        void log(std::string message) override;

    private:
        Ui::LoggingWidget* ui;
    };
}