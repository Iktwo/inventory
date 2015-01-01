#include "product.h"

Product::Product(const QString &name, QObject *parent) :
    QObject(parent),
    mName(name),
    mQuantity(0)
{

}

Product::Product(int id, const QString &name, QObject *parent) :
    QObject(parent),
    mName(name),
    mId(id),
    mQuantity(0)
{
}

Product::Product(int id, const QString &name, int quantity, QObject *parent) :
    QObject(parent),
    mName(name),
    mId(id),
    mQuantity(quantity)
{

}

int Product::id() const
{
    return mId;
}

QString Product::name() const
{
    return mName;
}

int Product::quantity() const
{
    return mQuantity;
}

void Product::setId(int id)
{
    if (mId == id)
        return;

    mId = id;
    emit idChanged();
}

void Product::setName(const QString &name)
{
    if (mName == name)
        return;

    mName = name;
    emit nameChanged();
}

void Product::setQuantity(int quantity)
{
    if (mQuantity == quantity)
        return;

    mQuantity = quantity;
    emit quantityChanged();
}
