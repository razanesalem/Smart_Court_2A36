
#include "Accuser.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

using namespace std;
Accuser::Accuser()
{
    id="";
    nom="";
    prenom="";
    affaire="";
    etat="";

}
Accuser::Accuser(QString id, QString nom,QString prenom, QString affaire, QString etat )
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->affaire=affaire;
    this->etat=etat;
   }
/*QString Accuser::getnom(){return  nom;}
QString Accuser::getprenom(){return  prenom;}
QString Accuser::getetat(){return  etat;}
QString Accuser::getaffaire(){return  affaire;}
QString Accuser::getid(){return  id;}
void Accuser::setnom(QString n){nom=n;}
void Accuser::setprenom(QString n){prenom=n;}
void Accuser::setID(QString n){id=n;}
void Accuser::setEtat(QString n){etat=n;}
void Accuser::setAffaire(QString n){affaire=n;}*/



bool Accuser::ajouter(Ui::MainWindow *ui)
{
    QSqlQuery q;


        q.prepare("INSERT INTO GS_ACCUSEES (ID,NOM,PRENOM,ETAT,AFFAIRE) VALUES (:id,:nom,:prenom,:etat,:affaire)");
        q.bindValue(":id",ui->lineEdit_id->text());
        q.bindValue(":nom",ui->lineEdit_Nom->text());
        q.bindValue(":prenom",ui->lineEdit_Prenom->text());
        q.bindValue(":etat",ui->radioButton_2->text());
        q.bindValue(":affaire",ui->lineEdit_affaire->text());



        if (    q.exec())
        {
            std::cout << "ca marche ! 🙂" << std::endl;

            QMessageBox msgBox ;
                    msgBox.setText("accuser ajoute ");
                    msgBox.exec();
            return true ;
        }
        else
        {
            std::cout<< "Ça marche pas ! :(" <<std::endl;

            QMessageBox msgBox ;
                    msgBox.setText("accuser n est pas ajoute ");
                    msgBox.exec();
                    return false;
        }
}

bool Accuser::Modifier(Ui::MainWindow *ui)
{
   QSqlQuery q;
   q.prepare("INSERT INTO GS_ACCUSEES (ID,NOM,PRENOM,ETAT,AFFAIRE) VALUES (:id,:nom,:prenom,:etat,:affaire)");
   q.bindValue(":id",ui->lineEdit_ID_2->text());
   q.bindValue(":nom",ui->lineEdit_Nom_2->text());
   q.bindValue(":prenom",ui->lineEdit_Prenom_2->text());
   q.bindValue(":etat",ui->radioButton_3->text());
   q.bindValue(":affaire",ui->lineEdit_affaire_2->text());


   if(q.exec())
   {
       if (    q.exec())
       {
           std::cout << "Ça marche ! 🙂" << std::endl;

           QMessageBox msgBox ;
                   msgBox.setText("les informations accuser  ont ete modifie ");
                   msgBox.exec();
           return true ;
       }
       else
       {
           std::cout<< "Ça marche pas ! :(" <<std::endl;

           QMessageBox msgBox ;
                   msgBox.setText("les informations accuser n ont pas modifie ");
                   msgBox.exec();
                   return false;
       }
}
}

bool Accuser::supprimer(Ui::MainWindow *ui)
{
    QSqlQuery q;

         q.prepare("DELETE FROM GS_ACCUSEES WHERE ID ='"+ui->lineEdit_id->text()+"'");


         if(q.exec())
         {
             QMessageBox msgBox ;
                     msgBox.setText("la valise a ete supprimee ");
                     msgBox.exec();
             return true;
         }
         else

{
             QMessageBox msgBox ;
                     msgBox.setText("la valise n'est pas supprimee' ");
                     msgBox.exec();
             return false;
}
}


void Accuser::AfficherTable(Ui::MainWindow *ui)
{
    QSqlQuery q;
    QSqlQueryModel *modal=new QSqlQueryModel();
    q.prepare("select * from GS_ACCUSEES");
    q.exec();
    modal->setQuery(q);
    ui->tableView->setModel(modal);
}
