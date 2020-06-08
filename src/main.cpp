#include <QApplication>

#include "gui/MainWindow/MainWindow.hpp"


// TODO: REMOVE!!

#include "domain/Request.hpp"
#include "domain/Response.hpp"
#include "domain/RequestListener.hpp"
#include "domain/TempLogger.hpp"
#include "domain/CppRestRequestListener.hpp"

using namespace backing::domain;

int main(int argc, char** argv)
{
    const auto& appName = "Backing";

    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/main"));
    QApplication::setApplicationDisplayName(appName);
    QApplication::setApplicationName(appName);


    const auto& listenFor = std::make_shared<Request>();
    listenFor->method = "GET";
    listenFor->baseUri = "http://localhost:5000";
    listenFor->resource = "/";

    const auto& respondWith = std::make_shared<Response>();
    respondWith->statusCode = 200;
    respondWith->body = "Hallo";

    const auto& logger = std::make_shared<TempLogger>();
    const auto& listener = std::make_shared<CppRestRequestListener>(logger);

    listener->listenFor(listenFor).respondWith(respondWith);
    listener->startListening();

    backing::gui::MainWindow window;
    window.show();

    return QApplication::exec();
}