#include <QApplication>

#include "domain/CppRestRequestListener.hpp"

#include "domain/ListenerFactory.hpp"
#include "domain/QtLogger.hpp"
#include "gui/MainWindow/MainWindow.hpp"
#include "gui/widget/LoggingWidget/LoggingWidget.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    const auto& appName = "Backing";
    const auto& logger = std::make_shared<backing::domain::QtLogger>();
    const auto& listenerFactory = std::make_shared<backing::domain::ListenerFactory>();
    const auto& listener = listenerFactory->getListener();
    const auto& loggingWidget = new backing::gui::widget::LoggingWidget(logger.get());

    listener->setLogger(logger);

    QApplication::setWindowIcon(QIcon(":/icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    backing::gui::MainWindow window(loggingWidget, listener);
    window.show();

    return QApplication::exec();
}