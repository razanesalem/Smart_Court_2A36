#include "accuse.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
using namespace std;


accuse::accuse()
{
    id="";
    nom="";
    prenom="";
    affaire="";
    etat="";

}
accuse::accuse(QString id, QString nom,QString prenom, QString affaire, QString etat )
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->affaire=affaire;
    this->etat=etat;
   }
QString accuse::getnom(){return  nom;}
QString accuse::getprenom(){return  prenom;}
QString accuse::getetat(){return  etat;}
QString accuse::getaffaire(){return  affaire;}
QString accuse::getid(){return  id;}
QString accuse::getID1(){return  id1;}
void accuse::setnom(QString n){nom=n;}
void accuse::setID1(QString n){id1=n;}
void accuse::setprenom(QString n){prenom=n;}
void accuse::setID(QString n){id=n;}
void accuse::setEtat(QString n){etat=n;}
void accuse::setAffaire(QString n){affaire=n;}

//ajout d'un accuse
void accuse::ajouter_accuse(accuse c){

    QString sQuery="INSERT INTO GS_ACCUSER (ID_ACC,NOM,PRENOM,ETAT,AFFAIRES) VALUES (:id,:nom,:prenom,:etat,:affaire)";

    QSqlQuery qry;

    qry.prepare(sQuery);
    qry.bindValue(":id",c.getid());
    qry.bindValue(":nom",c.getnom());
    qry.bindValue(":prenom",c.getprenom());
    qry.bindValue(":etat",c.getetat());
    qry.bindValue(":affaire",c.getaffaire());

    if(qry.exec())
    {
        QSound s("C:/Users/Zakraoui/Pictures/gestion_accuser/wave (2).mp3");
             s.play();
        QMessageBox::information(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row created and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not created and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


bool accuse::supprimer_accuse(accuse c)
{
QString id_ac =id;


    QString sQuery="DELETE FROM GS_ACCUSER WHERE ID_ACC='"+id_ac+"'";

    QSqlQuery qry;

    qry.prepare(sQuery);
    qry.bindValue(":id",id_ac);
    return  qry.exec();

}

void accuse::modifier_accuse(accuse c)
{
 QSqlQuery qry;
         qry.prepare ("UPDATE GS_ACCUSER set  NOM =:nom, PRENOM = :prenom, ETAT = :etat, AFFAIRES = :affaire where ID_ACC = :id" );

        qry.bindValue(":id",c.getid());
        qry.bindValue(":nom",c.getnom());
        qry.bindValue(":prenom",c.getprenom());
        qry.bindValue(":etat",c.getetat());
        qry.bindValue(":affaire",c.getaffaire());
        if(qry.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row updated and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
     {
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not updated and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

QSqlQueryModel *accuse::afficher_accuse()
{
   QString sQuery="SELECT ID_ACC,NOM,PRENOM,ETAT,AFFAIRES FROM GS_ACCUSER";

   QSqlQueryModel* model=new QSqlQueryModel();

   QSqlQuery qry;

   qry.prepare(sQuery);

   qry.exec();
   model->setQuery(qry);
   return model;}


  /* QSqlQuery qry1;

  // QString sQuery="SELECT ID_AFF FROM FAIRE";

   QSqlQueryModel* model1=new QSqlQueryModel();

   qry1.prepare("SELECT ID_AFF FROM FAIRE");
   qry1.exec();
   model1->setQuery(qry1);
return model;


}*/
QSqlQueryModel *accuse::afficher_accuse01()
{
   /* QString sQuery="SELECT ID_ACC,NOM,PRENOM,ETAT,AFFAIRES FROM GS_ACCUSER";

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model->setQuery(qry);*/

    QSqlQuery qry1;

   // QString sQuery="SELECT ID_AFF FROM FAIRE";

    QSqlQueryModel* model1=new QSqlQueryModel();

    qry1.prepare("SELECT ID_AFF FROM FAIRE");
    qry1.exec();
    model1->setQuery(qry1);

    return model1;}



QSqlQueryModel* accuse::chercher_accuse(QString rech){
    QString sQuery="SELECT ID_ACC,NOM,PRENOM,ETAT,AFFAIRES FROM GS_ACCUSER WHERE NOM LIKE'%"+rech+"%' or PRENOM LIKE'%"+rech+"%' or ID_ACC LIKE'%"+rech+"%'";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}


bool accuse::chercher_accuse01(QString id)
{


    QSqlQuery test ;
      test.prepare("SELECT COUNT(*)  FROM GS_ACCUSER WHERE ID_ACC= :id");
      test.bindValue(":id",id);
      test.exec();
      if (test.next())
      {
    if (test.value(0).toInt() == 1)
    {
        return true;
    }
       else
        return false;
      }

}

QSqlQueryModel* accuse::afficher_accuse_trie_prenom(){
    QString sQuery="SELECT *FROM GS_ACCUSER ORDER BY PRENOM";

    QSqlQueryModel*model1=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model1->setQuery(qry);
return model1
        ;}
QSqlQueryModel* accuse::afficher_accuse_trie_nom(){
    QString sQuery="SELECT ID_ACC,NOM,PRENOM,ETAT,AFFAIRES FROM GS_ACCUSER ORDER BY NOM";

    QSqlQueryModel*model1=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model1->setQuery(qry);
return model1
        ;}
QSqlQueryModel* accuse::afficher_accuse_trie_ID(){
    QString sQuery="SELECT ID_ACC,NOM,PRENOM,ETAT,AFFAIRES FROM GS_ACCUSER ORDER BY ID_ACC";
    QSqlQueryModel*model1=new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare(sQuery);

    qry.exec();
    model1->setQuery(qry);
return model1
        ;}

/*void accuse::ajouter_accuse(accuse c)
{
    QString sQuery="INSERT INTO GS_ACCUSER (ID_ACC,NOM,PRENOM,ETAT) VALUES (:id,:nom,:prenom,:etat)";
    QString sQuery1="INSERT INTO GS_AFFAIRE_JURIDIQUE (ID_AFF) VALUES (:id1)";

    QSqlQuery qry,qry1;

    qry.prepare(sQuery);
    qry.bindValue(":id",c.getid());
    qry.bindValue(":nom",c.getnom());
    qry.bindValue(":prenom",c.getprenom());
    qry.bindValue(":etat",c.getetat());
    qry1.prepare(sQuery1);

    qry1.bindValue(":id1",c.getID1());

    if(qry.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row created and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not created and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
*/
