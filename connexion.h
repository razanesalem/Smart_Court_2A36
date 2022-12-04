#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
class Connexion
{
public:
    Connexion();
    bool createconnect();
    int Authentification(QString login,QString pwd);
private:
    QString log;
    QString mdps;
};


#endif // CONNECTION_H
