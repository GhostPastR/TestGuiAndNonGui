TEMPLATE = subdirs

SUBDIRS += \
    ConvertStruct \
    ProcessTask \
    TestGui \
    TestNonGui \

TestGui.depends = ConvertStruct ProcessTask
TestNonGui.depends = ConvertStruct ProcessTask
