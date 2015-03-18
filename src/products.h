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
        QuantityRole,
        ImageRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int count() const;

    Q_INVOKABLE bool addProduct(int id, const QString &name, int quantity, const QString &image);
    Q_INVOKABLE void removeProduct(int id);

    Q_INVOKABLE Product* itemAt(int index);

    void initDB();
    void retrieveProducts();

signals:
    void showMessage(QString message, Notifications::NotificationType type, Notifications::NotificationDuration duration);
    void countChanged();
    void productAddedToDB(int id, const QString &name, int quantity, const QString &image);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QObjectList mProducts;
    QSqlDatabase mDB;
    QSqlQuery m_activitiesQuery;

    void addProductToModel(QObject *product);
    void addProductToDB(int id, const QString &name, int quantity, const QString &image);
    void removeProductFromDB(int idProduct);

    void setProductName(int idProduct, const QString &name);
    void setProductQuantity(int idProduct, int quantity);
    void setProductImage(int idProduct, const QString &image);

    int lastProductId();

private slots:
    void addRegisteredProduct(int id, const QString &name, int quantity, const QString &image);
};

#endif // PRODUCTS_H
