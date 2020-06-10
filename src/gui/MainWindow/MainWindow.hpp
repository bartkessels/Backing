#pragma once

#include <list>
#include <memory>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>

#include "domain/Listener.hpp"
#include "gui/widget/LoggingWidget/LoggingWidget.hpp"
#include "gui/widget/MethodWidget/MethodWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace backing::gui
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(const std::shared_ptr<widget::LoggingWidget>& loggingWidget, const std::shared_ptr<domain::Listener>& listener, QWidget* parent = nullptr);
        ~MainWindow() override;

    private:
        void connectSignals();

        Ui::MainWindow* ui;

        const std::shared_ptr<domain::Listener>& listener;
        const std::shared_ptr<widget::LoggingWidget>& loggingWidget;

    private slots:
        void resetButtons();
    };
}