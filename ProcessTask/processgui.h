#ifndef PROCESSGUI_H
#define PROCESSGUI_H

#include <memory>
#include <QWidget>

class QProcess;
class SmFlagCalc;
class SmCommand;
class SmData;

class ProcessGui : public QWidget
{
    Q_OBJECT
public:
    ProcessGui(QWidget *parent = nullptr);
    ~ProcessGui() override;

    void send( unsigned int command );

protected:
    std::unique_ptr<SmData> data_;

    bool valid() const;

    int msecTime() const;
    void setMsecTime( int msecTime );
    virtual void testLoop( unsigned int command ) = 0;

private slots:
    void slotTimeOut();

private:
    bool valid_;
    int msecTime_;
    std::unique_ptr<QTimer> timer_;
    std::unique_ptr<QProcess> process_;
    std::unique_ptr<SmFlagCalc> flagProcess_;
    std::unique_ptr<SmCommand> command_;   

    bool createProcessChild( const QString &pathProcess, const QStringList &parametr );
    void killProcessChild();
};

inline bool ProcessGui::valid() const
{
    return valid_;
}

inline int ProcessGui::msecTime() const
{
    return msecTime_;
}

#endif // PROCESSGUI_H
