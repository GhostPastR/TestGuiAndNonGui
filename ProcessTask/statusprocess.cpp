#include "statusprocess.h"
#include <QSharedMemory>
#include <QDebug>

SmFlagCalc::SmFlagCalc( bool isNew )
{
    flagCalc_ = std::make_unique<QSharedMemory>( "SmflagCalc" );
    if( isNew ) {
        flagCalc_->create( sizeof( StatusProcess ) );
        setFlagNonCalc();
    }
}

bool SmFlagCalc::attashSm()
{
    return flagCalc_->attach();
}

bool SmFlagCalc::detachSm()
{
    return flagCalc_->detach();
}

StatusProcess SmFlagCalc::statusFlag() const
{
    StatusProcess _status = StatusProcess::SP_UNASSIGNED;
    if( flagCalc_->lock() ){
        StatusProcess *flag = reinterpret_cast<StatusProcess*>( flagCalc_->data() );
        if( flag == nullptr ) {
            flagCalc_->unlock();
            return _status;
        }
        _status = *flag;
        flagCalc_->unlock();
    }
    return _status;
}

bool SmFlagCalc::setFlagNonCalc()
{
    return setFlag( StatusProcess::SP_NON_CALC );
}

bool SmFlagCalc::setFlagBeginCalc()
{
    return setFlag( StatusProcess::SP_BEGIN_CALC );
}

bool SmFlagCalc::setFlagCalc()
{
    return setFlag( StatusProcess::SP_CALC );
}

bool SmFlagCalc::setFlagEndCalc()
{
    return setFlag( StatusProcess::SP_END_CALC );
}

bool SmFlagCalc::setFlagTerminate()
{
    return setFlag( StatusProcess::SP_TERMINATE );
}

bool SmFlagCalc::setFlag( StatusProcess status )
{
    if( flagCalc_->lock() ){
        StatusProcess *flag = reinterpret_cast<StatusProcess*>( flagCalc_->data() );
        if( flag == nullptr ) {
            flagCalc_->unlock();
            return false;
        }
        *flag = status;
        flagCalc_->unlock();
    }
    return false;
}





SmCommand::SmCommand( bool isNew )
{
    command_ = std::make_unique<QSharedMemory>( "SmCommand" );
    if( isNew )
        command_->create( sizeof ( unsigned int ) );
}

bool SmCommand::attachSm()
{
    return command_->attach();
}

bool SmCommand::detachSm()
{
    return command_->detach();
}

void SmCommand::setCommand( unsigned int command )
{
    if( command_->lock() ){
        unsigned int *_sm = reinterpret_cast<unsigned int*>( command_->data() );
        if( _sm == nullptr ) {
            command_->unlock();
            return;
        }
        *_sm = command;
        command_->unlock();
    }
}

unsigned int SmCommand::command()
{
    unsigned int _command = 0;
    if( command_->lock() ){
        unsigned int *_sm = reinterpret_cast<unsigned int*>( command_->data() );
        if( _sm == nullptr ) {
            command_->unlock();
            return _command;
        }
        _command = *_sm;
        command_->unlock();
    }
    return _command;
}





SmData::SmData( const QString &nameSharedMemory, bool isNew )
{
    data_ = std::make_unique<QSharedMemory>( nameSharedMemory );
    if( isNew ) {
        data_->create( 1024 * 1024 );
    }
}

bool SmData::attachDs()
{
    return data_->attach();
}

bool SmData::detachDs()
{
    return data_->detach();
}

const char *SmData::readData()
{
    if( data_->lock() ) {
        char *_data = reinterpret_cast<char*>( data_->data() );
        if( _data == nullptr ){
            data_->unlock();
            return nullptr;
        }
        auto _d = _data;
        data_->unlock();
        return _d;
    }
    return nullptr;
}

bool SmData::writeData( const char *data, size_t len )
{
    if( data_->lock() ) {
        char *_data = reinterpret_cast<char*>( data_->data() );
        if( _data == nullptr ){
            data_->unlock();
            return false;
        }
        std::char_traits<char>::copy( _data, data, len );
        data_->unlock();
        return true;
    }
    return false;
}
