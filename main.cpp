#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("ProfX Software");
    QCoreApplication::setOrganizationDomain("profx.zx6.ru");
    QCoreApplication::setApplicationName("TaxXIP");
    MainWindow w;
    w.show();

    return a.exec();
}
