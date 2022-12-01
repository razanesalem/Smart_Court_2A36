#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QDebug>
#include "accuse.h"
#include <QSqlError>
#include <QSqlQuery>
class Connection
{
public:
    Connection();
    bool createconnect();
    void closeconnect();
};


#endif // CONNEXION_H
