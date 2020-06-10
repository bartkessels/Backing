#include "gui/MainWindow/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace backing::gui;

MainWindow::MainWindow(widget::LoggingWidget* loggingWidget, const std::shared_ptr<domain::Listener>& listener, QWidget* parent):
    QMainWindow(parent),
    listener(listener),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    this->connectSignals();

    this->ui->loggingWidget->addWidget(loggingWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals()
{
    connect(ui->btnStartListening, &QPushButton::pressed,
            this, [=]() {
                const auto& uri = ui->textUri->text().toStdString();
                listener->start(uri);

                this->resetButtons();
            });

    connect(ui->btnStopListening, &QPushButton::pressed,
            this, [=]() {
                listener->stop();

                this->resetButtons();
            });

    connect(ui->btnAddMethodToMock, &QPushButton::pressed,
            this, [=]() {
                auto method = ui->textNewMethod->text().toStdString();
                auto widget = new widget::MethodWidget(listener, method, ui->tabListeners);

                ui->tabListeners->addTab(widget, method.c_str());
                ui->textNewMethod->clear();
            });

    connect(ui->tabListeners, &QTabWidget::tabCloseRequested,
            this, [=](int requestedTabToCloseIndex) {
                const auto& method = ui->tabListeners->tabBar()->tabText(requestedTabToCloseIndex).toStdString();

                listener->unregisterMethod(method);
                delete ui->tabListeners->widget(requestedTabToCloseIndex);
            });
}

void MainWindow::resetButtons()
{
    ui->btnStopListening->setEnabled(!ui->btnStopListening->isEnabled());
    ui->btnStartListening->setEnabled(!ui->btnStartListening->isEnabled());
}