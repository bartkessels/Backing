#include "gui/widget/LoggingWidget/LoggingWidget.hpp"
#include "./ui_LoggingWidget.h"

using namespace backing::gui::widget;

LoggingWidget::LoggingWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::LoggingWidget)
{
    ui->setupUi(this);
}

LoggingWidget::~LoggingWidget()
{
    delete ui;
}

void LoggingWidget::log(std::string message)
{
    ui->listLogs->addItem(message.c_str());
}