#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QObject>
#include <QColor>

class Notifications : public QObject
{
    Q_OBJECT
    Q_ENUMS(NotificationType NotificationDuration)

public:
    explicit Notifications(QObject *parent = 0);

    enum NotificationType {
        Error = 1,
        Succes,
        Generic
    };

    enum NotificationDuration {
        Infinite = -1,
        Short = 750,
        Medium = 1500,
        Long = 3000
    };

    Q_INVOKABLE static QColor colorForType(NotificationType type);
};

#endif // NOTIFICATIONS_H
