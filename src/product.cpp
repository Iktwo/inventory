#include "product.h"

Product::Product(const QString &name, QObject *parent) :
    QObject(parent),
    m_name(name),
    m_quantity(0)
{
}

Product::Product(int id, const QString &name, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_name(name),
    m_quantity(0)
{
}

Product::Product(int id, const QString &name, int quantity, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_name(name),
    m_quantity(quantity)
{
}

Product::Product(int id, const QString &name, int quantity, const QString &image, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_name(name),
    m_quantity(quantity),
    m_image(image)
{
}

int Product::id() const
{
    return m_id;
}

QString Product::name() const
{
    return m_name;
}

int Product::quantity() const
{
    return m_quantity;
}

void Product::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

void Product::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged();
}

void Product::setQuantity(int quantity)
{
    if (m_quantity == quantity)
        return;

    m_quantity = quantity;
    emit quantityChanged();
}

QString Product::image() const
{
    return m_image;
}

void Product::setImage(QString arg)
{
    if (m_image == arg)
        return;

    m_image = arg;
    emit imageChanged(arg);
}
