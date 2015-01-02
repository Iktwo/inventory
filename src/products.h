#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QAbstractListModel>
#include <QtSql>

#include "notifications.h"

class Product;
class Products : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit Products(QObject *parent = 0);
    ~Products();

    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        QuantityRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int count() const;

    Q_INVOKABLE void addProduct(const QString &name, int id);
    Q_INVOKABLE void removeProduct(int id);

    Q_INVOKABLE Product* itemAt(int index);

    void initDB();
    void retrieveProducts();

signals:
    void showMessage(QString message, Notifications::NotificationType type, Notifications::NotificationDuration duration);
    void countChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QObjectList mProducts;
    QSqlDatabase mDB;
    QSqlQuery m_activitiesQuery;

    void addProductToModel(QObject *product);
    void addProductToDB(const QString &product);
    void removeProductFromDB(int idProduct);

    void setProductName(int idProduct, const QString &name);

    int lastProductId();
};

#endif // PRODUCTS_H
