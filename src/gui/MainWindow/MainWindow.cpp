#include "gui/MainWindow/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace backing::gui;

MainWindow::MainWindow(const std::shared_ptr<widget::LoggingWidget>& loggingWidget, const std::shared_ptr<domain::RequestListenerFactory>& listenerFactory, QWidget* parent):
    QMainWindow(parent),
    listenerFactory(listenerFactory),
    loggingWidget(loggingWidget),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    this->connectSignals();
    this->setupDefaultTabs();

    this->ui->loggingWidget->addWidget(loggingWidget.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals()
{
    connect(ui->btnStartListening, &QPushButton::pressed,
            this, &MainWindow::startListening);
    connect(ui->btnStopListening, &QPushButton::pressed,
            this, &MainWindow::stopListening);

    connect(ui->btnAddMethodToMock, &QPushButton::pressed,
            this, [=]() {
        const auto& methodName = ui->textNewMethod->text().toStdString();
        const auto& requestListener = listenerFactory->getRequestListener();
        auto responseWidget = new widget::RequestListenerWidget(requestListener, ui->tabListeners);

        ui->tabListeners->addTab(responseWidget, ui->textNewMethod->text());
    });

    connect(ui->tabListeners, &QTabWidget::tabCloseRequested,
            this, [=](int requestedTabToCloseIndex) {
        delete ui->tabListeners->widget(requestedTabToCloseIndex);
    });
}

void MainWindow::setupDefaultTabs()
{
    this->addNewTab("GET");
    this->addNewTab("POST");
}

void MainWindow::addNewTab(const std::string& method)
{
    const auto& requestListener = listenerFactory->getRequestListener();
    auto responseWidget = new widget::RequestListenerWidget(requestListener, ui->tabListeners);

    ui->tabListeners->addTab(responseWidget, method.c_str());
}

void MainWindow::startListening()
{
    auto uri = ui->textUri->text().toStdString();

    for (int i = 0; i < ui->tabListeners->count(); i++) {
        auto method = ui->tabListeners->tabText(i).toStdString();
        const auto& widget = ui->tabListeners->widget(i);
        const auto& listener = dynamic_cast<widget::RequestListenerWidget*>(widget);

        try {
            listener->startListening(method, uri);
        } catch(std::exception& ex) {
            QMessageBox::critical(this, "An error occurred", ex.what());
        }
    }

    this->resetButtons();
}

void MainWindow::stopListening()
{
    for (int i = 0; i < ui->tabListeners->count(); i++) {
        const auto& widget = ui->tabListeners->widget(i);
        const auto& listener = dynamic_cast<widget::RequestListenerWidget*>(widget);

        try {
            listener->stopListening();
        } catch(std::exception& ex) {
            QMessageBox::critical(this, "An error occurred", ex.what());
        }
    }

    this->resetButtons();
}

void MainWindow::resetButtons()
{
    ui->btnStopListening->setEnabled(!ui->btnStopListening->isEnabled());
    ui->btnAddMethodToMock->setEnabled(!ui->btnAddMethodToMock->isEnabled());
    ui->btnStartListening->setEnabled(!ui->btnStartListening->isEnabled());
}