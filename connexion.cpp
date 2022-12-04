#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test");
db.setUserName("nouram");//inserer nom de l'utilisateur
db.setPassword("nouram");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
      return test;
}

int Connexion::Authentification(QString log,QString mdps)
{
    QSqlDatabase bd = QSqlDatabase::database();

        QSqlQuery query;
        QSqlQuery query2;

        query.prepare("SELECT NOM_EM FROM EMPLOYEES WHERE NOM_EM= \'"+log+"\' AND  ID_EM'"+mdps+"\'");
        query2.prepare("SELECT * FROM AUTHENTIFICATION where LOG=\'"+log+"\' AND MDPS=\'"+mdps+"\'");

        query.exec();
        query2.exec();
        if (query.next())
        {
             return 1;
        }
        /*if (query2.next())
        {
             return 2;
        }*/
        else {
            return 0;
        }
}
