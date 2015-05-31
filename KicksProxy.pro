#-------------------------------------------------
#
# Project created by QtCreator 2015-05-25T22:43:02
#
#-------------------------------------------------

QT       += core network

TARGET = KicksProxy

#CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    singleinstance.cpp \
    packets/packetid.cpp \
    packets/cryptography.cpp \
    packets/packethandler.cpp \
    network/proxyclient.cpp \
    network/proxyserver.cpp \
    network/servermanager.cpp \
    network/workertask.cpp \
    settings.cpp \
    argumentsparser.cpp \
    network/udpproxy.cpp

HEADERS += \
    singleinstance.h \
    packets/packetid.h \
    packets/packettypes.h \
    packets/cryptography.h \
    packets/packethandler.h \
    network/proxyserver.h \
    network/proxyclient.h \
    network/servermanager.h \
    network/workertask.h \
    settings.h \
    argumentsparser.h \
    network/udpproxy.h


OTHER_FILES += proxy.ini

# Copy settings file to the output directory
copydata.commands = $(COPY_DIR) $$PWD/proxy.ini $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
