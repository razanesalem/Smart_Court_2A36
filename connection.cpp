#include "connection.h"

Connection::Connection(){}
//testcommit
bool Connection::createconnection()
{
    bool test=false;
    db=QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("test.db");
    db.setUserName("razane");
    db.setPassword("razane");

    if (db.open())
    test=true;

    return  test;
}

void Connection::closeconnection(){db.close();}


