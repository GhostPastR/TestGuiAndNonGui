#include "testnongui.h"
#include <QLineEdit>
#include <QString>
#include "liststructsystem.h"
#include "statusprocess.h"

TestNonGui::TestNonGui( QObject *parent ) : ProcessNonGui(parent)
{

}

TestNonGui::~TestNonGui()
{
}

void TestNonGui::testLoop( unsigned int command )
{
    if( command == 1 ) {
        data_->attachDs();
        auto _p = data_->readData();

        ConverByte<ItemShared> _sd;
        auto _d = _sd.convertBytes( _p );
        data_->detachDs();

        dataTable_.item_.append( { QString::fromStdString( _d->value1_ ),
                                   QString::fromStdString( _d->value2_ ) } );

        _d->value3_ = dataTable_.item( 0 ).v3_.toStdString();

        std::cout << _d->value1_ << std::endl;
        std::cout << _d->value2_ << std::endl;
        std::cout << _d->value3_ << std::endl;

        data_->attachDs();

        _sd.setData( *_d.get() );
        auto _data = _sd.bytes();
        data_->writeData( _data.first.get(), _data.second );
        data_->detachDs();
        send( 1 );
    }



//    if( command == 1 ) {
//        send( 1 );
//    }
//    else if( command == 2 ) {
//        while(true){}
//        send( 2 );
//    }
//    else if( command == 3 ) {
//        int a = 1 /0;
//        send( 3 );
//    }
//    else {
//        send( 0 );
//    }
}

