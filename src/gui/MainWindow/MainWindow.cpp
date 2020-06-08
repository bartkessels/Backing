#include "gui/MainWindow/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace backing::gui;

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}