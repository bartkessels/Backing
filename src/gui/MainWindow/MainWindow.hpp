#pragma once

#include <list>
#include <memory>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>

#include "domain/RequestListenerFactory.hpp"
#include "gui/widget/LoggingWidget/LoggingWidget.hpp"
#include "gui/widget/RequestListenerWidget/RequestListenerWidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace backing::gui
{
    class MainWindow: public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(const std::shared_ptr<widget::LoggingWidget>& logginWidget, const std::shared_ptr<domain::RequestListenerFactory>& factory, QWidget* parent = nullptr);
        ~MainWindow() override;

    private:
        void connectSignals();

        Ui::MainWindow* ui;
        const std::shared_ptr<domain::RequestListenerFactory>& listenerFactory;
        const std::shared_ptr<widget::LoggingWidget>& loggingWidget;

    private slots:
        void setupDefaultTabs();
        void addNewTab(const std::string& method);
        void startListening();
        void stopListening();
        void resetButtons();
    };
}