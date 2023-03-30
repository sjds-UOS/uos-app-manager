QT += core gui
QT += dtkwidget dtkgui dtkcore

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uos_app_manager
TEMPLATE = app

SOURCES += \
        main.cpp

RESOURCES +=         resources.qrc
