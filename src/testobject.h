#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <QObject>

class TestObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
    explicit TestObject(QObject *parent = 0);

    QString name() const;

signals:
    void nameChanged();

public slots:

private:
    QString mName;

};

#endif // TESTOBJECT_H
