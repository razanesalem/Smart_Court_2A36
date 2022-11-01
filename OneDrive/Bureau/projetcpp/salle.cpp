#include"salle.h"
#include <QDebug>
#include <iostream>
#include <list>
#include <QString>
salle::salle()//constructeur par défaut
{
    numsalle=0;
    capacite=0;

}
salle::salle(int numsalle,int capacite)//paramétré
{
    this->numsalle=numsalle;
    this->capacite=capacite;
}
bool salle::ajouter_salle()
{

    QSqlQuery query;
   // QString string_numsalle = QString::number(numsalle);
   // QString string_capacite = QString::number(capacite);
    query.prepare("INSERT INTO SALLE (NUM_SALLE,CAPACITE) "
                  "VALUES (:0,:1)");
    query.bindValue(":0",numsalle);
    query.bindValue(":1",capacite);

    return query.exec();
}
QSqlQueryModel * salle::afficher_salle()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM SALLE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM_SALLE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CAPACITE"));




    return model;
}
bool salle::modifier_salle(int numsalle, int capacite)
{
    QSqlQuery query;
    query.prepare("UPDATE SALLE SET NUM_SALLE=:numsalle,CAPACITE=:capacite   WHERE (NUM_SALLE=:numsalle )");
    query.bindValue(":numsalle",numsalle);
    query.bindValue(":capacite",capacite);

    return query.exec();
}
bool salle::supprimer_salle( int numsalle)
{
    QSqlQuery query;
    query.prepare("DELETE FROM SALLE WHERE NUM_SALLE =:numsalle ");
    query.bindValue(":numsalle", numsalle);

    return  query.exec();
}

