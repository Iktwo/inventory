#include "notifications.h"

#include <QDebug>

Notifications::Notifications(QObject *parent) : QObject(parent)
{

}

QColor Notifications::colorForType(Notifications::NotificationType type)
{
    switch (type) {
    case Error:
        return QColor("#e74c3c");
    case Succes:
        return QColor("#2ecc71");
    case Generic:
    default:
        return QColor("#3498db");
    }
}
