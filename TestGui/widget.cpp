#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "liststructsystem.h"
#include "statusprocess.h"

Widget::Widget(QWidget *parent)
    : ProcessGui(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::testLoop( unsigned int command )
{
    if( command == 1 ) {
        auto _p = data_->readData();
        if( _p != nullptr ) {
            ConverByte<ItemShared> _sd;
            auto _d = _sd.convertBytes( _p );


            int _row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow( ui->tableWidget->rowCount() );
            ui->tableWidget->setItem( _row, 0, new QTableWidgetItem( QString::fromStdString( _d->value1_ ) ) );
            ui->tableWidget->setItem( _row, 1, new QTableWidgetItem( QString::fromStdString( _d->value2_ ) ) );
            ui->tableWidget->setItem( _row, 2, new QTableWidgetItem( QString::fromStdString( _d->value3_ ) ) );
        }
    }
    else if( command == 2 ) {
        qDebug() << "Command 2";
    }
    else if( command == 3 ) {
        qDebug() << "Command 3";
    }
    else
        qDebug() << "Command non";
}


void Widget::on_pushButton_clicked()
{
//    send( 1 );
}

void Widget::on_pushButton_2_clicked()
{
//    send( 2 );
}

void Widget::on_pushButton_3_clicked()
{
//    send( 3 );
}



void Widget::on_pushButton_4_clicked()
{
    ItemShared _d;
    _d.value1_ = ui->lineEdit->text().toStdString();
    _d.value2_ = ui->lineEdit_2->text().toStdString();
    ConverByte<ItemShared> _sd( _d );
    auto _p = _sd.bytes();
    data_->writeData( _p.first.get(), _p.second );
    qDebug() << _p.second;
    send( 1 );
}
