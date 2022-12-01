#ifndef ADMIN_H
#define ADMIN_H

#include<QString>
#include<QSqlQueryModel>
#include <QDebug>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
class admin
{
public:
    admin();
    admin(QString,QString,QString);
    bool Login();
    QString afficherRole();


private:
    int id;
    QString username,password,role;

};

#endif // ADMIN_H
