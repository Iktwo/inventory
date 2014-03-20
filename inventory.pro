QT += quick widgets sql

SOURCES += \
    src/main.cpp \
    src/testobject.cpp \
    src/dbaccessor.cpp \
    src/product.cpp \
    src/products.cpp \
    src/translator.cpp

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    qml/main.qml \
    resources/data/db.sql \
    qml/LanguageSelector.qml \
    qml/Products.qml \
    qml/ProductDetails.qml

HEADERS += \
    src/testobject.h \
    src/dbaccessor.h \
    src/product.h \
    src/products.h \
    src/translator.h

TRANSLATIONS = \
           translation_sp.ts

QMAKE_CXXFLAGS += -std=gnu++11
