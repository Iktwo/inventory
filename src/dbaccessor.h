#ifndef DBACCESSOR_H
#define DBACCESSOR_H

#include <QObject>
#include <QtSql>

//class Activity;
class DBAccessor : public QObject
{
    Q_OBJECT
public:    
    explicit DBAccessor(QObject *parent = 0);
    ~DBAccessor();
    QVariantMap activityTypes();

public slots:
    void initDB();
    void firstActivities();
    void getMoreActivities();
    void setAscTime(bool);

signals:
    void error(QString error);
    void initializationFinished();
    void fetchedActivities(QObjectList activities);
    
private:
    QSqlDatabase m_db;
    QSqlQuery m_activitiesQuery;
    int m_fetched;
    int m_lastIdFetched;
    //Activity *lastActivity;
    QString m_ascTime;

};

#endif // DBACCESSOR_H
