#ifndef PROCESSNONGUI_H
#define PROCESSNONGUI_H

#include <memory>
#include <QObject>

class QTimer;
class SmFlagCalc;
class SmCommand;
class SmData;


class ProcessNonGui : public QObject
{
    Q_OBJECT
public:
    ProcessNonGui( QObject *parent = nullptr );
    ~ProcessNonGui() override;

    void send( unsigned int command );

public slots:
    void slotTimeOut();

protected:
    std::unique_ptr<SmData> data_;

    virtual void testLoop( unsigned int command ) = 0;

private:
    int msecTime_;

    std::unique_ptr<QTimer> timer_;
    std::unique_ptr<SmFlagCalc> flagProcess_;
    std::unique_ptr<SmCommand> command_;
};

#endif // PROCESSNONGUI_H
