#include "connexion.h"
#include <QMessageBox>
#include<QDebug>
#include <QSqlDatabase>
#include<QtSql/QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;


QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");
db.setUserName("dali");//inserer nom de l'utilisateur
db.setPassword("dali123");//inserer mot de passe de cet utilisateur


if (db.open())
test=true;
  return  test;
}
void Connection::closeconnect(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.close();}
