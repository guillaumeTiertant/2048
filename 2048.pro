QT       += core gui quick

TARGET = 2048test

TEMPLATE = app

RESOURCES += \
    2048.qrc

HEADERS += \
    cpp/contexte.h \
    cpp/processgame.h

SOURCES += \
    cpp/main.cpp \
    cpp/contexte.cpp \
    cpp/processgame.cpp

DISTFILES += \
    android-sources/AndroidManifest.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
