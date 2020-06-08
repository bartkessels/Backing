#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace backing::gui
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow() override;

    private:
        Ui::MainWindow* ui;
    };
}