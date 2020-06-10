#pragma once

#include <memory>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QTreeWidget>
#include <QWidget>
#include <utility>

#include "domain/Listener.hpp"
#include "domain/Response.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MethodWidget; }
QT_END_NAMESPACE

namespace backing::gui::widget
{
    class MethodWidget: public QWidget
    {
    public:
        explicit MethodWidget(std::shared_ptr<domain::Listener> listener, std::string method, QWidget* parent = nullptr);
        ~MethodWidget() override;

        std::shared_ptr<backing::domain::Response> getResponse();

    private:
        void connectSignals();

        Qt::ItemFlags treeWidgetItemFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
        std::shared_ptr<domain::Listener> listener;
        std::string method;
        Ui::MethodWidget* ui;
    };
}