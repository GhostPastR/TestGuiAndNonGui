#ifndef TESTNONGUI_H
#define TESTNONGUI_H

#include <processnongui.h>
#include <datashared.h>
#include "testdatatable.h"

class TestNonGui : public ProcessNonGui
{
    Q_OBJECT
public:
     TestNonGui( QObject *parent = nullptr );
    ~TestNonGui() override;

protected:
     void testLoop( unsigned int command ) override;

private:
     TestDataTable dataTable_;
};
#endif // TESTNONGUI_H
