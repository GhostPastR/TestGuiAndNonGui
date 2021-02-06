#include "processgui.h"
#include <QTimer>
#include <QProcess>
#include <QSharedMemory>
#include <QDebug>

#include "statusprocess.h"

ProcessGui::ProcessGui( QWidget *parent )
    : QWidget(parent)
{
    valid_ = true;
    timer_ = std::make_unique<QTimer>( this );
    connect( timer_.get(), &QTimer::timeout, this, &ProcessGui::slotTimeOut );
    msecTime_ = 50;

    {
        //Считывания данных с кофигурационного файла
    }

    flagProcess_ = std::make_unique<SmFlagCalc>();
    command_ = std::make_unique<SmCommand>();
    data_ = std::make_unique<SmData>( "Data" );
}

ProcessGui::~ProcessGui()
{
    this->killProcessChild();
}

void ProcessGui::send( unsigned int command )
{
//    auto _nonGui = "C:/1/build-CreateTrajectory-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/test_task/TestNonGui/debug/TestNonGui.exe";
        auto _nonGui = "TestNonGui.exe";
    if( !valid_ ) {
        createProcessChild( _nonGui, QStringList() );
        flagProcess_->setFlagTerminate();
    }
    if( !process_ ) {
        createProcessChild( _nonGui, QStringList() );
    }
    if( ( flagProcess_->statusFlag() == StatusProcess::SP_NON_CALC ) ||
        ( flagProcess_->statusFlag() == StatusProcess::SP_TERMINATE ) ||
        ( flagProcess_->statusFlag() == StatusProcess::SP_UNASSIGNED )) {
        command_->setCommand( command );
        flagProcess_->setFlagBeginCalc();
        timer_->start( msecTime_ );
    }
    else {
        qDebug() << "Процесс занят";
    }
}

void ProcessGui::slotTimeOut()
{
    if( !process_ )
        return;
    if( process_->exitStatus() == QProcess::CrashExit ) {
        valid_ = false;
        qDebug() << "Процесс завершился аварийно!";
        timer_->stop();
        return;
    }
    if( flagProcess_->statusFlag() == StatusProcess::SP_END_CALC ) {
        flagProcess_->setFlagNonCalc();
        this->timer_->stop();
        this->testLoop( command_->command() );
    }
}

void ProcessGui::setMsecTime( int msecTime )
{
    msecTime_ = msecTime;
}

bool ProcessGui::createProcessChild( const QString &pathProcess,
                                     const QStringList &parametr )
{
    killProcessChild();
    process_ = std::make_unique<QProcess>( this );
    process_->start( pathProcess, parametr );
    bool _f = process_->waitForStarted();
    if ( !_f ) {
        qDebug() << "Не удалось запустить процесс!";
        process_.reset();
    }
    valid_ = true;
    return _f;
}

void ProcessGui::killProcessChild()
{
    if( !process_ )
        return;
    process_->kill();
    flagProcess_->setFlagNonCalc();
    if ( process_->waitForFinished() )
        process_.reset();
    timer_->stop();
}

