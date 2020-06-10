#include "gui/widget/MethodWidget/MethodWidget.hpp"
#include "./ui_MethodWidget.h"

using namespace backing::gui::widget;

MethodWidget::MethodWidget(std::shared_ptr<domain::Listener> listener, std::string method, QWidget* parent):
    QWidget(parent),
    listener(std::move(listener)),
    method(std::move(method)),
    ui(new Ui::MethodWidget())
{
    ui->setupUi(this);
    this->connectSignals();

    this->ui->textStatusCode->setValidator(new QIntValidator());
}

MethodWidget::~MethodWidget()
{
    delete ui;
}

std::shared_ptr<backing::domain::Response> MethodWidget::getResponse()
{
    auto response = std::make_shared<domain::Response>();
    std::string statusCode = ui->textStatusCode->text().toStdString();
    std::string body = ui->textBody->document()->toPlainText().toStdString();

    for(int i = 0; i < ui->treeHeaders->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeHeaders->topLevelItem(i);
        const auto& header = item->text(0).toStdString();
        const auto& value = item->text(1).toStdString();

        response->headers.insert_or_assign(header, value);
    }

    response->statusCode = std::stoi(statusCode);
    response->body = body;

    return response;
}

void MethodWidget::connectSignals()
{
    connect(ui->btnAddHeader, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeHeaders);
                row->setText(0, "Key");
                row->setText(1, "Value");
                row->setFlags(treeWidgetItemFlags);
            });

    connect(ui->btnRemoveHeader, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeHeaders->currentItem();
            });

    connect(ui->btnUpdate, &QPushButton::pressed,
            this, [=]() {
               listener->registerMethod(method, getResponse());
            });
}