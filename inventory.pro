QT += quick widgets sql svg

SOURCES += \
    src/main.cpp \
    src/dbaccessor.cpp \
    src/product.cpp \
    src/products.cpp \
    src/translator.cpp \
    src/notifications.cpp

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    qml/*.qml \
    qml/products/*.qml \
    qml/pages/products/*.qml \
    resources/data/db.sql

HEADERS += \
    src/dbaccessor.h \
    src/product.h \
    src/products.h \
    src/translator.h \
    src/notifications.h

TRANSLATIONS = \
           translation_sp.ts

QMAKE_CXXFLAGS += -std=gnu++11

QML_IMPORT_PATH += qml

DISTFILES += \
    qml/NotificationBar.qml \
    qml/CustomDropArea.qml

lupdate_only{
    SOURCES += \
        qml/*.qml \
        qml/components/*.qml \
        qml/pages/*.qml \
        qml/pages/products/*.qml
}
