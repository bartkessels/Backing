#include "gui/widget/ResponseWidget/ResponseWidget.hpp"

#include <utility>
#include "./ui_ResponseWidget.h"

using namespace backing::gui::widget;

ResponseWidget::ResponseWidget(std::string  methodName, QWidget* parent):
    QWidget(parent),
    ui(new Ui::ResponseWidget()),
    methodName(std::move(methodName))
{
    ui->setupUi(this);
}

ResponseWidget::~ResponseWidget()
{
    delete ui;
}