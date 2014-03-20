#include "testobject.h"

TestObject::TestObject(QObject *parent) :
    QObject(parent), mName("XXXX")
{
}

QString TestObject::name() const
{
    return mName;
}
