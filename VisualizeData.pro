#-------------------------------------------------
#
# Project created by QtCreator 2023-09-12T13:47:25
#
#-------------------------------------------------

QT       += core gui
QT += charts
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualizeData
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        source/abstractcard.cpp \
        source/alarmsummary.cpp \
        source/circulardial.cpp \
        source/circulardialsummary.cpp \
        source/datasummary.cpp \
        source/dynamicalarm.cpp \
        source/dynamicsearth.cpp \
        source/histroychart.cpp \
        source/main.cpp \
        source/piechart.cpp \
        source/piewidget.cpp \
        source/rollalarm.cpp \
        source/title.cpp \
        source/visualizedata.cpp \
        source/qcustomplot.cpp

HEADERS += \
        include/abstractcard.h \
        include/alarmsummary.h \
        include/circulardial.h \
        include/circulardialsummary.h \
        include/datasummary.h \
        include/dynamicalarm.h \
        include/dynamicsearth.h \
        include/histroychart.h \
        include/piechart.h \
        include/piewidget.h \
        include/rollalarm.h \
        include/title.h \
        include/visualizedata.h \
        include/qcustomplot.h

INCLUDEPATH += include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/res.qrc
