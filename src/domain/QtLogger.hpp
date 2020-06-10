#pragma once

#include <QObject>
#include <QString>

#include "domain/Logger.hpp"

namespace backing::domain
{
    class QtLogger: public QObject, public Logger
    {
        Q_OBJECT

    public:
        explicit QtLogger(QObject* parent = nullptr);

        void log(const std::string& message) override;

    signals:
        void writeLogToGui(QString);
    };
}