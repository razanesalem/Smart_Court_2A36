#ifndef EMPLOYER_H
#define EMPLOYER_H
#include <QDate>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class Employer
{
    int CIN;
    int Nbanne;
    QDate date_nes  ;
    QString nom,prenom,poste;

public:
    Employer(){};
    Employer(int,int,QDate,QString,QString,QString);
    //getters
    int getCIN();
    int getNbanne();
    QString getnom();
     QString getprenom();
      QDate getdate_nes();
       QString getposte();

     //setters
       void setCIN(int CIN){this->CIN=CIN;}
       void setnom(QString n){nom=n;}
       void setprenom(QString p){prenom=p;}
       void setdate_nes(QDate d){date_nes=d;}

       void setposte(QString pos){poste=pos;}
       //fonctionnalite
       bool ajouter();
       QSqlQueryModel* afficher();
       bool supprimer(int);
       bool modifier();
        QSqlQueryModel*afficher_id();
        QSqlQueryModel* afficher_EM_trie_Nbanne();
        QSqlQueryModel* afficher_EM_trie_date();
        QSqlQueryModel *rechercher(QString );
        QSqlQueryModel *recherchercode(QString CIN);
        QSqlQuery request(QString);



};

#endif // EMPLOYER_H
