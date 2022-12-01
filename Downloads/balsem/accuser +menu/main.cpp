#include "mainwindow.h"
#include "connexion.h"
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "accuse.h"
#include <QDebug>
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QTextEdit>
#include "connexion.h"
#include "mainwindow.h"
#include <QPrinter>
#include <QDesktopServices>
#include <QSqlQueryModel>
#include <QDialog>
#include <QObject>

QT_BEGIN_NAMESPACE
int main(int argc, char *argv[])
{accuse d;
    QApplication a(argc, argv);
    MainWindow w;
    Connection c;

    bool test=c.createconnect();

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    return a.exec();
}
