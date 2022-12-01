#ifndef ACCUSE_H
#define ACCUSE_H
//#include "mainwindow.h"
#include<QString>
#include<qsqlquerymodel.h>
//#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include "QMainWindow"
using namespace std;
class accuse
{
public:
    accuse();

    accuse(QString,QString,QString,QString,QString);
   //setteres
    void setnom(QString n);
    void setprenom(QString n);
    void setID(QString n);
    void setAffaire(QString n);
    void setEtat(QString n);
    void  setID1(QString n);

    //getters
    QString getnom();
    QString getprenom();
    QString getid();
    QString getaffaire();
    QString getetat();
    QString getID1();
    //~Accuser();
    //crud
    void ajouter_accuse(accuse c);
    bool supprimer_accuse(accuse c);
    void modifier_accuse(accuse c);
    QSqlQueryModel* chercher_accuse(QString rech);
    QSqlQueryModel* afficher_accuse_trie_nom();
    QSqlQueryModel* afficher_accuse_trie_prenom();
    QSqlQueryModel* afficher_accuse_trie_ID();
    QSqlQueryModel* afficher_accuse();
    QSqlQueryModel* afficher_accuse01();
    bool chercher_accuse01(QString id);

protected:
QString id,nom,prenom,etat,affaire,id1;
};

#endif // ACCUSE_H
