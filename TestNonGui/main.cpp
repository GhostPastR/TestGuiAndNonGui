#include "testnongui.h"

#include <QApplication>
#include <QLineEdit>

#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestNonGui w;
//    QTimer timer;
//    timer.connect( &timer, &QTimer::timeout, &w, &TestNonGui::slotTimeOut );
//    timer.start( 1000 );
//    qDebug() << "===========2";

    return a.exec();
}
