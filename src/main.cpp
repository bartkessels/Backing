#include <QApplication>

#include "domain/CppRestRequestListener.hpp"

#include "domain/ListenerFactory.hpp"
#include "gui/MainWindow/MainWindow.hpp"
#include "gui/widget/LoggingWidget/LoggingWidget.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    const auto& appName = "Backing";
    const auto& loggingWidget = std::make_shared<backing::gui::widget::LoggingWidget>();
    const auto& listenerFactory = std::make_shared<backing::domain::ListenerFactory>(loggingWidget);
    const auto& listener = listenerFactory->getListener();

    QApplication::setWindowIcon(QIcon(":/icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);

    backing::gui::MainWindow window(loggingWidget.get(), listener);
    window.show();

    return QApplication::exec();
}