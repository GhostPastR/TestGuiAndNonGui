#ifndef WIDGET_H
#define WIDGET_H

#include <processgui.h>
#include <datashared.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public ProcessGui
{
    Q_OBJECT

public:
    Widget( QWidget *parent = nullptr );
    ~Widget() override;

protected:
    void testLoop( unsigned int command ) override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
