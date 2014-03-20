#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QVariantMap>
#include <QtWidgets/QApplication>
#include <QTranslator>

class Translator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString tr READ tr NOTIFY languageChanged)
    Q_PROPERTY(QString language READ language NOTIFY languageChanged)

public:
    explicit Translator(QApplication *app, const QString &source, QObject *parent = 0);

    void addTranslation(const QString &name, const QString &file);
    void setSource(const QString &source);

    Q_INVOKABLE void translate(const QString &language);

    QString tr() const;
    QString language() const;

signals:
    void languageChanged();

private:
    QApplication *m_app;
    QString mSource;
    QString mLanguage;
    QVariantMap mTranslations;
    QTranslator mQtTranslator;
    void removeTranslation();
};

#endif // TRANSLATOR_H
