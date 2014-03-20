#include "dbaccessor.h"
//#include "activity.h"
//#include "activityvalue.h"

#define ERROR_SQL emit error("SQL error in " + QString(Q_FUNC_INFO) + ". Error: " \
    + sql.lastError().text() + ". Query: "+sql.lastQuery())

const int FetchLimit = 15;
static const char ConnectionName[] = "medical_db";

DBAccessor::DBAccessor(QObject *parent) :
    QObject(parent),
    m_fetched(0),
    m_lastIdFetched(-1),
    m_ascTime("DESC")
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", ConnectionName);
    m_db.setDatabaseName("db.sqlite");
}

DBAccessor::~DBAccessor()
{
    m_db.close();
    m_db = QSqlDatabase();
    QSqlDatabase::removeDatabase(ConnectionName);
}

void DBAccessor::initDB()
{
    if (!m_db.open()) {
        emit error("DB error in " + QString(Q_FUNC_INFO) + ". Error: "+ m_db.lastError().text());
        return;
    }

    QFile dbScript(":/sql/db.sql");

    if (!dbScript.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "initDB() Error: Can't read resource dbScript " << dbScript.error();
        exit(0);
    }

    m_db.transaction();

    while (!dbScript.atEnd()) {
        QString query = dbScript.readLine();

        if (!query.startsWith("--") && query.simplified().length()>1) {
            QSqlQuery sql(QSqlDatabase::database(ConnectionName));
            sql.prepare(query);

            if (!sql.exec())
                ERROR_SQL;
        }
    }

    m_db.commit();

    emit initializationFinished();
}

void DBAccessor::getMoreActivities()
{
    QString query = QString("SELECT DISTINCT idActivity, timestamp, event_type "
                            "FROM activities "
                            "NATURAL JOIN activity_values "
                            "ORDER BY timestamp %1, idActivity "
                            "LIMIT :limit OFFSET :offset").arg(m_ascTime);

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);
    sql.bindValue(":limit", FetchLimit);
    sql.bindValue(":offset", m_fetched);

    if (!sql.exec())
        ERROR_SQL;

    QList<int> activityIds;
    QObjectList activities;

    while (sql.next()) {
        QDateTime dt = QDateTime::fromString(sql.value(1).toString(), "yyyyMMdd-HHmmss");
        /*Activity *act = new Activity(dt, sql.value(2).toInt());
        activityIds.append(sql.value(0).toInt());
        activities.append(act);*/
    }

    for (int i = 0; i < activityIds.count(); ++i) {
        // Going trough each activity to get its values
        query = QString("SELECT idActivityValueType, value, info "
                        "FROM activity_values "
                        "WHERE idActivity = :idActivity");

        sql.prepare(query);
        sql.bindValue(":idActivity",activityIds.at(i));

        if (!sql.exec())
            ERROR_SQL;

        while (sql.next()) {
            /*ActivityValue *val = new ActivityValue(sql.value(0).toInt(),
                                                   sql.value(1),
                                                   sql.value(2).toString());

            qobject_cast<Activity*>(activities.at(i))->addValue(val);*/
        }

        m_fetched++;
    }

    emit fetchedActivities(activities);
}

void DBAccessor::firstActivities()
{
    // Retrieve first FetchLimit activities
    QString query = QString("SELECT DISTINCT idActivity, timestamp, event_type "
                            "FROM activities "
                            "NATURAL JOIN activity_values "
                            "ORDER BY timestamp %1, idActivity "
                            "LIMIT :limit").arg(m_ascTime);

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);
    sql.bindValue(":limit", FetchLimit);

    if (!sql.exec())
        ERROR_SQL;

    QList<int> activityIds;
    QObjectList activities;

    while (sql.next()) {
        QDateTime dt = QDateTime::fromString(sql.value(1).toString(), "yyyyMMdd-HHmmss");
        /*Activity *act = new Activity(dt, sql.value(2).toInt());
        activityIds.append(sql.value(0).toInt());
        activities.append(act);*/
    }

    m_fetched = 0;

    for (int i = 0; i < activityIds.count(); ++i) {
        // Going trough each activity to get its values
        query = QString("SELECT idActivityValueType, value, info "
                        "FROM activity_values "
                        "WHERE idActivity = :idActivity ");

        sql.prepare(query);
        //sql.bindValue(":idActivity",activityIds.at(i));

        if (!sql.exec())
            ERROR_SQL;

        while (sql.next()) {
            /*ActivityValue *val = new ActivityValue(sql.value(0).toInt(),
                                                   sql.value(1),
                                                   sql.value(2).toString());

            qobject_cast<Activity*>(activities.at(i))->addValue(val);*/
        }

        m_fetched++;
    }

    emit fetchedActivities(activities);
}

QVariantMap DBAccessor::activityTypes()
{
    QVariantMap types;

    QString query = "SELECT idActivityValueType, type FROM activity_value_types";

    QSqlQuery sql(QSqlDatabase::database(ConnectionName));
    sql.prepare(query);

    if (!sql.exec())
        ERROR_SQL;

    while (sql.next())
        types.insert(sql.value(0).toString(), sql.value(1).toString());

    m_db.close();

    return types;
}

void DBAccessor::setAscTime(bool value)
{
    if (value) {
        m_ascTime = "ASC";
    } else {
        m_ascTime = "DESC";
    }

    firstActivities();
}
