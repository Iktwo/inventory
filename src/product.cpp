#include "product.h"

Product::Product(const QString &name, QObject *parent) :
    QObject(parent),
    mName(name)
{

}

Product::Product(int id, const QString &name, QObject *parent) :
    QObject(parent),
    mName(name),
    mId(id)
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
