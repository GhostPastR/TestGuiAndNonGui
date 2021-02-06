#ifndef TESTDATATABLE_H
#define TESTDATATABLE_H

#include <QList>
#include <QPair>
#include <QString>

struct Item {
    QString v1_;
    QString v2_;
    QString v3_;
};

class TestDataTable
{
public:
    TestDataTable();

    Item item( int index ) const;


    QList<QPair<QString, QString>> item_;
};

#endif // TESTDATATABLE_H
