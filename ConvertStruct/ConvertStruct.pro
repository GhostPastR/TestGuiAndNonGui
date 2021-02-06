TARGET = ConvertStruct
TEMPLATE = lib


QMAKE_CXXFLAGS_DEBUG += -O3
QMAKE_CFLAGS_DEBUG  += -O3

SOURCES +=

HEADERS += \
    convertbyte.h \
    liststructsystem.h \
    structsharememory.h \
    uniontype.h

include(../project.pri)
out = $$setPath(../)
out = $$configLib()
