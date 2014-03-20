#include "products.h"

#include "product.h"

#include <QDebug>

#define ERROR_SQL emit error("SQL error in " + QString(Q_FUNC_INFO) + ". Error: " \
    + sql.lastError().text() + ". Query: "+sql.lastQuery())

static const char ConnectionName[] = "inventory_db";

Products::Products(QObject *parent) :
    QAbstractListModel(parent)
{
    mDB = QSqlDatabase::addDatabase("QSQLITE", ConnectionName);
    mDB.setDatabaseName("db.sqlite");

    initDB();
    retrieveProducts();
}

Products::~Products()
{
    mDB.close();
    mDB = QSqlDatabase();
    QSqlDatabase::removeDatabase(ConnectionName);
}

void Products::initDB()
{
    if (!mDB.open()) {
        /// TODO: notify UI that there's a problem with DB
        qDebug() << "DB error in " + QString(Q_FUNC_INFO) + ". Error: "+ mDB.lastError().text();
        return;
    }

    QFile dbScript(":/sql/db.sql");

    if (!dbScript.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "initDB() Error: Can't read resource dbScript " << dbScript.error();
        exit(0);
    }

    mDB.transaction();

    while (!dbScript.atEnd()) {
        QString query = dbScript.readLine();

        if (!query.startsWith("--") && query.simplified().length()>1) {
            QSqlQuery sql(QSqlDatabase::database(ConnectionName));
            sql.prepare(query);

            if (!sql.exec())
                ERROR_SQL;
        }
    }

    mDB.commit();
}

void Products::retrieveProducts()
{
    QString query = QString("SELECT * FROM products ORDER BY name");

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);

    if (!sql.exec())
        ERROR_SQL;

    while (sql.next())
        addProductToModel(new Product(sql.value(0).toInt(), sql.value(1).toString()));
}

int Products::rowCount(const QModelIndex &parent) const
{
    /// This functions returns the number of elements in the model
    Q_UNUSED(parent)
    return mProducts.count();
}

QVariant Products::data(const QModelIndex &index, int role) const
{
    /// This functions retrieves data for a given index

    /// If index is out of range return nothing
    if (index.row() < 0 || index.row() >= mProducts.count())
        return QVariant();

    Product *product = qobject_cast<Product*>(mProducts[index.row()]);
    if (role == IdRole)
        return product->id();
    else if (role == NameRole)
        return product->name();

    return QVariant();
}

bool Products::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //qDebug() << "setting data for role: " << role;
    //return false;
    if (index.isValid() && role == NameRole && !value.toString().simplified().isEmpty()) {
        Product *product = qobject_cast<Product*>(mProducts[index.row()]);
        product->setName(value.toString());
        setProductName(product->id(), value.toString());
        emit dataChanged(index, index);
        return true;
    } else {
        return false;
    }
}

int Products::count() const
{
    return rowCount();
}

void Products::addProduct(const QString &name)
{
    /// TODO: maybe check if product is already in DB ??
    if (name.simplified().isEmpty()) {
        /// Show error in UI
        return;
    }

    addProductToDB(name);
    addProductToModel(new Product(lastProductId(), name));
}

void Products::removeProduct(int id)
{
    /// Remove product from model and from DB

    int index = -1;
    for (int i = 0; i < rowCount(); ++i) {
        if (qobject_cast<Product*>(mProducts[i])->id() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        /// TODO: show error in UI, this shouldn't happen in normal flow
        return;
    }

    removeProductFromDB(id);

    Product *product = qobject_cast<Product*>(mProducts[index]);
    beginRemoveRows(QModelIndex(), index, index);
    mProducts.removeAt(index);
    endRemoveRows();
    emit countChanged();
    delete product;
}

Product* Products::itemAt(int index)
{
    if (index < 0 || index >= mProducts.count())
        return 0;
    else
        return qobject_cast<Product*>(mProducts[index]);
}

QHash<int, QByteArray> Products::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[QuantityRole] = "quantity";
    return roles;
}

void Products::addProductToModel(QObject *product)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mProducts.append(product);
    endInsertRows();
    emit countChanged();
}

void Products::addProductToDB(const QString &product)
{
    QString query = QString("INSERT INTO products (\"name\") "
                            "VALUES (:name)");

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);
    sql.bindValue(":name", product);

    if (!sql.exec())
        ERROR_SQL;
}

void Products::removeProductFromDB(int idProduct)
{
    QString query = QString("DELETE FROM products WHERE "
                            "\"idProduct\" = :idProduct");

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);
    sql.bindValue(":idProduct", idProduct);

    if (!sql.exec())
        ERROR_SQL;
}

void Products::setProductName(int idProduct, const QString &name)
{
    QString query = QString("UPDATE products SET "
                            "\"name\" = :name "
                            "WHERE "
                            "\"idProduct\" = :idProduct ");

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);
    sql.bindValue(":idProduct", idProduct);
    sql.bindValue(":name", name);

    if (!sql.exec())
        ERROR_SQL;
}

int Products::lastProductId()
{
    QString query = QString("SELECT max(rowid) from products");

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);

    if (!sql.exec())
        ERROR_SQL;

    while (sql.next())
        return sql.value(0).toInt();

    return -1;
}
