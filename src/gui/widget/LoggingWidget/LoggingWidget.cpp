#include "gui/widget/LoggingWidget/LoggingWidget.hpp"
#include "./ui_LoggingWidget.h"

using namespace backing::gui::widget;

LoggingWidget::LoggingWidget(domain::QtLogger* logger, QWidget* parent):
    QWidget(parent),
    ui(new Ui::LoggingWidget),
    logger(logger)
{
    ui->setupUi(this);

    connect(logger, &domain::QtLogger::writeLogToGui,
            this, [=](const QString& message) {
                ui->listLogs->addItem(message);
            });
}

LoggingWidget::~LoggingWidget()
{
    delete ui;
}