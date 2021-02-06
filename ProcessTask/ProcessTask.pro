QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProcessTask
TEMPLATE = lib

SOURCES += \
    datashared.cpp \
    processgui.cpp \
    processnongui.cpp \
    statusprocess.cpp

HEADERS += \
    datashared.h \
    processgui.h \
    processnongui.h \
    statusprocess.h

include(../project.pri)
out = $$setPath(../)
out = $$configLib()
