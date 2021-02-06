#include "processnongui.h"
#include <QTimer>
#include <QSharedMemory>
#include "statusprocess.h"

ProcessNonGui::ProcessNonGui( QObject *parent ) : QObject(parent)
{
    timer_ = std::make_unique<QTimer>( this );
    connect( timer_.get(), &QTimer::timeout, this, &ProcessNonGui::slotTimeOut );
    msecTime_ = 50;
    timer_->start( msecTime_ );

    flagProcess_ = std::make_unique<SmFlagCalc>( false );
    command_ = std::make_unique<SmCommand>( false );
    data_ = std::make_unique<SmData>( "Data", false );
}

ProcessNonGui::~ProcessNonGui()
{

}

void ProcessNonGui::send( unsigned int command )
{
    flagProcess_->attashSm();
    if( flagProcess_->statusFlag() == StatusProcess::SP_CALC ) {
        command_->attachSm();
        command_->setCommand( command );
        command_->detachSm();
        flagProcess_->setFlagEndCalc();
        flagProcess_->detachSm();
        timer_->start( msecTime_ );
    }
    else
        flagProcess_->detachSm();

}

void ProcessNonGui::slotTimeOut()
{

    flagProcess_->attashSm();
    if( flagProcess_->statusFlag() == StatusProcess::SP_BEGIN_CALC ) {
        timer_->stop();
        flagProcess_->setFlagCalc();
        flagProcess_->detachSm();
        unsigned int _command = 0;
        command_->attachSm();
        _command = command_->command();
        command_->detachSm();
        this->testLoop( _command );
        timer_->start( msecTime_ );
    }
    else
        flagProcess_->detachSm();
}
