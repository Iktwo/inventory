#include "translator.h"

#include <QSettings>
#include <QDebug>

static const char DefaultLanguage[] = "EN";

Translator::Translator(QApplication *app, const QString &source, QObject *parent) :
    QObject(parent),
    m_app(app),
    mSource(source)
{
}

void Translator::addTranslation(const QString &name, const QString &file)
{
    if (!mTranslations.contains(name))
        mTranslations.insert(name, file);
}

QString Translator::tr() const
{
    return "";
}

QString Translator::language() const
{
    return mLanguage;
}

void Translator::setSource(const QString &source)
{
    mSource = source;
}

void Translator::translate(const QString &language)
{
    qDebug() << Q_FUNC_INFO << language;
    if (language.toUpper() == "DEFAULT" || language == DefaultLanguage || language.isEmpty())
        removeTranslation();

    if (mTranslations.contains(language) && mQtTranslator.load(mTranslations.value(language).toString(), mSource)) {
        qDebug() << Q_FUNC_INFO << "Translated to: " << language;

        QSettings settings;
        settings.setValue("language", language);
        m_app->installTranslator(&mQtTranslator);
        mLanguage = language;
        emit languageChanged();
    }
}

void Translator::removeTranslation()
{
    QSettings settings;
    settings.setValue("language", "DEFAULT");
    m_app->removeTranslator(&mQtTranslator);
    mLanguage = DefaultLanguage;
    emit languageChanged();
}
