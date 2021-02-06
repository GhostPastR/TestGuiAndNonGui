#ifndef STATUSPROCESS_H
#define STATUSPROCESS_H

#include <memory>
#include <QString>

enum class StatusProcess
{
    SP_UNASSIGNED   = 0x0,
    SP_NON_CALC     = 0x1,
    SP_BEGIN_CALC   = 0x2,
    SP_CALC         = 0x3,
    SP_END_CALC     = 0x4,
    SP_TERMINATE    = 0x5,
};


class QSharedMemory;

class SmFlagCalc
{
public:
    SmFlagCalc( bool isNew = true );
    ~SmFlagCalc() = default;

    bool attashSm();
    bool detachSm();

    StatusProcess statusFlag() const;

    bool setFlagNonCalc();
    bool setFlagBeginCalc();
    bool setFlagCalc();
    bool setFlagEndCalc();
    bool setFlagTerminate();

private:
    std::unique_ptr<QSharedMemory> flagCalc_;

    bool setFlag( StatusProcess status );
};





class SmCommand
{
public:
    SmCommand( bool isNew = true );
    ~SmCommand() = default;

    bool attachSm();
    bool detachSm();

    void setCommand( unsigned int command );
    unsigned int command();

private:
    std::unique_ptr<QSharedMemory> command_;
};




class SmData
{
    SmData( const SmData &temp ) = delete;
    SmData( SmData &&temp ) = delete;

    SmData &operator=( const SmData &temp ) = delete;
    SmData &operator=( SmData &&temp ) = delete;

public:
    SmData( const QString &nameSharedMemory, bool isNew = true );
    ~SmData() = default;

    bool attachDs();
    bool detachDs();


    const char *readData();
    bool writeData( const char *data , size_t len );

private:
    std::unique_ptr<QSharedMemory> data_;
};


#endif // STATUSPROCESS_H
