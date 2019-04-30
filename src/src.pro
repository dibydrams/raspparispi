#-------------------------------------------------
#
# Project created by QtCreator 2019-04-17T12:46:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += charts
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
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
        Abstract_API.cpp \
        addrtocoord.cpp \
        apiborneswifi.cpp \
        apibornes_elec.cpp \
        apievenementsmv.cpp \
        apimeteo.cpp \
        apivelib.cpp \
        dialogmeteo.cpp \
        indiceuv.cpp \
        meteo.cpp \
        pollution.cpp \
        prevision.cpp \
        apiquefaire.cpp \
        apikiosques.cpp\
        custombutton.cpp \
        icon.cpp \
        main.cpp \
        mainwindow.cpp \
        pharmapi.cpp \
        utilitaire.cpp \
        widgetmap.cpp \
    	stoppoint.cpp \
    	transport.cpp \
    	apiratp_station.cpp \
    	uiratp.cpp \
        apiratp_global.cpp \
        apiterrasses.cpp \
        sanisette.cpp \
        apiratp_search.cpp \
        apiespacesverts.cpp \
        theatre.cpp \
        apifontaines.cpp\
      	uiratp.cpp \
        apiratp_global.cpp \
        sanisette.cpp \
        apiratp_search.cpp \
        apiespacesverts.cpp \
        theatre.cpp
    



HEADERS += \
        Abstract_API.h \
    addrtocoord.h \
        apiborneswifi.h \
        apibornes_elec.h \
        apievenementsmv.h \
        apimeteo.h \
        apiquefaire.h \
        apiratp_station.h \
        apivelib.h \
        custombutton.h \
        apikiosques.h \
        dialogmeteo.h \
        icon.h \
        indiceuv.h \
        mainwindow.h \
        meteo.h \
        pharmapi.h \
        pollution.h \
        prevision.h \
        stoppoint.h \
        transport.h \
        uiratp.h \
        widgetmap.h \
        apiratp_global.h \
        apiterrasses.h \
    sanisette.h \
    theatre.h \
    apiratp_search.h \
    apiespacesverts.h \
    apifontaines.h \

        meteo.h \
        pharmapi.h \
        pollution.h \
        prevision.h \
        stoppoint.h \
        transport.h \
        uiratp.h \
        utilitaire.h \
        widgetmap.h \
        apiratp_global.h \
        apiterrasses.h \
        sanisette.h \
        theatre.h \
        apiratp_search.h \
        apiespacesverts.h 



FORMS += \
	mainwindow.ui \
        uiratp.ui \
        dialogmeteo.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
        iconmeteo.qrc \
        sources.qrc
