#include <QApplication>

#include "domain/RequestListenerFactory.hpp"
#include "gui/MainWindow/MainWindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    const auto& appName = "Backing";
    const auto& loggingWidget = std::make_shared<backing::gui::widget::LoggingWidget>();
    const auto& listenerFactory = std::make_shared<backing::domain::RequestListenerFactory>(loggingWidget);

    QApplication::setWindowIcon(QIcon(":/icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    backing::gui::MainWindow window(loggingWidget, listenerFactory);
    window.show();

    return QApplication::exec();
}