#include <QApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QSettings>
#include <QDir>

#include "translator.h"

#include "notifications.h"
#include "product.h"
#include "products.h"

int main(int argc, char *argv[])
{
    // QByteArray data = "1";
    // qputenv("QML_IMPORT_TRACE", data);

    QScopedPointer<QApplication> app(new QApplication(argc, argv));

    QQmlApplicationEngine engine;

    QCoreApplication::setOrganizationName("Iktwo Corp.");
    QCoreApplication::setOrganizationDomain("iktwo.com");
    QCoreApplication::setApplicationName("Inventario");

    qRegisterMetaType<Notifications::NotificationType>("Notifications::NotificationType");
    qRegisterMetaType<Notifications::NotificationDuration>("Notifications::NotificationDuration");

    qmlRegisterType<Product>();
    qmlRegisterType<Notifications>("Notifications", 1, 0, "Notifications");

    Products products;
    engine.rootContext()->setContextProperty("productsModel", &products);

    /// Add translation files
    Translator translator(app.data(), ":/translations");
    translator.addTranslation("SP", "translation_sp.qm");
    engine.rootContext()->setContextProperty("translator", &translator);

    /// Retrieve last translation
    QSettings settings;
    translator.translate(settings.value("language", "SP").toString());

    QDir imagesDir("images");
    engine.rootContext()->setContextProperty("imagesDir", imagesDir.absolutePath());

    engine.addImportPath("qrc:/qml/qml");
    engine.load(QUrl("qrc:/qml/qml/main.qml"));

    return app->exec();
}
