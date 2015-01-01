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
    qml/main.qml \
    resources/data/db.sql \
    qml/LanguageSelector.qml \
    qml/Products.qml \
    qml/ProductDetails.qml

HEADERS += \
    src/dbaccessor.h \
    src/product.h \
    src/products.h \
    src/translator.h \
    src/notifications.h

TRANSLATIONS = \
           translation_sp.ts

QMAKE_CXXFLAGS += -std=gnu++11

DISTFILES += \
    qml/NotificationBar.qml

lupdate_only{
    SOURCES += qml/*.qml
}
