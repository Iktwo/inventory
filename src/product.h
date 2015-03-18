#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class Product : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id NOTIFY idChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int quantity READ quantity NOTIFY quantityChanged)
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged)

public:
    Product(const QString &name, QObject *parent = 0);
    Product(int id, const QString &name, QObject *parent = 0);
    Product(int id, const QString &name, int quantity, QObject *parent = 0);
    Product(int id, const QString &name, int quantity, const QString &image, QObject *parent = 0);

    int id() const;
    QString name() const;
    int quantity() const;

    void setId(int id);
    void setName(const QString &name);
    void setQuantity(int quantity);

    QString image() const;

public slots:
    void setImage(QString arg);

signals:
    void idChanged();
    void nameChanged();
    void quantityChanged();

    void imageChanged(QString arg);

private:
    int m_id;
    QString m_name;
    int m_quantity;
    QString m_image;
};

#endif // PRODUCT_H
