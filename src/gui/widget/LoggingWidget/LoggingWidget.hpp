#pragma once

#include <string>
#include <QString>
#include <QWidget>

#include "domain/QtLogger.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class LoggingWidget; }
QT_END_NAMESPACE

namespace backing::gui::widget
{
    class LoggingWidget: public QWidget
    {
    public:
        explicit LoggingWidget(domain::QtLogger* logger, QWidget* parent = nullptr);
        ~LoggingWidget() override;

    private:
        Ui::LoggingWidget* ui;
        domain::QtLogger* logger;
    };
}