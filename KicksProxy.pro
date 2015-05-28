#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T22:43:02
#
#-------------------------------------------------

QT       += core network gui

TARGET = KicksProxy

#CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    singleinstance.cpp \
    proxyserver.cpp \
    constants.cpp \
    proxyclient.cpp \
    workertask.cpp \
    packets/packetid.cpp \
    packets/cryptography.cpp \
    packets/packethandler.cpp

HEADERS += \
    singleinstance.h \
    proxyserver.h \
    constants.h \
    proxyclient.h \
    workertask.h \
    packets/packetid.h \
    packets/packettypes.h \
    packets/cryptography.h \
    packets/packethandler.h
