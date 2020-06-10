#include "domain/QtLogger.hpp"

using namespace backing::domain;

QtLogger::QtLogger(QObject* parent):
    QObject(parent)
{

}

void QtLogger::log(const std::string& message)
{
    emit writeLogToGui(message.c_str());
}