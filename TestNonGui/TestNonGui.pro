QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestNonGui
TEMPLATE = app

SOURCES += \
    main.cpp \
    testdatatable.cpp \
    testnongui.cpp

HEADERS += \
    testdatatable.h \
    testnongui.h

include(../project.pri)
out = $$setPath(../)
out = $$addLibs(ConvertStruct ProcessTask)
