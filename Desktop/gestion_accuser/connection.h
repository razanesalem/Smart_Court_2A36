#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "Accuser.h"
class Connection
{
public:
    Connection();
    bool createconnect();
    void closeconnect();
};

#endif // CONNECTION_H
