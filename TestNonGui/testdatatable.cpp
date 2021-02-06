#include "testdatatable.h"

TestDataTable::TestDataTable()
{

}

Item TestDataTable::item( int index ) const
{
    if( index < 0 )
        return Item();
    Item item;
    item.v1_ = item_.at( index ).first;
    item.v2_ = item_.at( index ).second;
    item.v3_ = item_.at( index ).first + item_.at( index ).second;
    return item;
}
