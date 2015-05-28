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
    constants.cpp \
    packets/packetid.cpp \
    packets/cryptography.cpp \
    packets/packethandler.cpp \
    network/proxyclient.cpp \
    network/proxyserver.cpp \
    network/workertask.cpp

HEADERS += \
    singleinstance.h \
    constants.h \
    packets/packetid.h \
    packets/packettypes.h \
    packets/cryptography.h \
    packets/packethandler.h \
    network/proxyserver.h \
    network/proxyclient.h \
    network/workertask.h
