#include "employer.h"
#include<QtDebug>
#include<QObject>

Employer::Employer(int CIN,int Nbanne,QDate date_nes ,QString nom,QString prenom,QString poste)
{   this->CIN=CIN;
    this->Nbanne=Nbanne;
    this->date_nes=date_nes;
    this->nom=nom;
    this->prenom=prenom;
    this->poste=poste;




}
    
bool Employer:: ajouter(){
    QSqlQuery query;
    QString res=QString::number(CIN);
    QString r=QString::number(Nbanne);

         query.prepare("INSERT INTO EMPLOYER (CIN, NBANNE,DATE_NAISSANCE,NOM,PRENOM,POSTE_ACTUELL) "
                       "VALUES (:CIN, :NBANNE, :DATE_NAISSANCE,:NOM,:PRENOM,:POSTE_ACTUELL)");
         query.bindValue(":CIN", res);
         query.bindValue(":NBANNE", r);
         query.bindValue(":DATE_NAISSANCE", date_nes);
         query.bindValue(":NOM",nom );
         query.bindValue(":PRENOM",prenom);
          query.bindValue(":POSTE_ACTUELL",poste);
         return query.exec();
}

QSqlQueryModel* Employer::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
         model->setQuery("select * from EMPLOYER");
         model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
         model->setHeaderData(1,Qt::Horizontal,QObject::tr("NBANNE"));
         model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
         model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOM"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("PRENOM"));
             model->setHeaderData(5,Qt::Horizontal,QObject::tr("POSTE_ACTUELL"));
         return model;
}
bool Employer:: supprimer(int CIN){
    QSqlQuery query;
             query.prepare("delete from EMPLOYER where cin=:CIN");
             query.bindValue(0, CIN);
             return query.exec();
}

bool Employer::modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE EMPLOYER SET CIN = :CIN, NBANNE = :NBANNE, DATE_NAISSANCE = :DATE_NAISSANCE, NOM = :NOM, PRENOM = :PRENOM , POSTE_ACTUELL = :POSTE_ACTUELL  WHERE CIN = :CIN");

    query.bindValue(":CIN", CIN);
    query.bindValue(":NBANNE", Nbanne);
    query.bindValue(":DATE_NAISSANCE", date_nes);
    query.bindValue(":NOM", nom);
    query.bindValue(":PRENOM", prenom);
    query.bindValue(":POSTE_ACTUELL", poste);

    return query.exec();
}


QSqlQueryModel * Employer::afficher_EM_trie_Nbanne()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM EMPLOYER ORDER BY NBANNE ;");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NBANNE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("POSTE_ACTUELL"));
    return model;
}
QSqlQueryModel* Employer:: afficher_EM_trie_date(){

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM EMPLOYER ORDER BY DATE_NAISSANCE ;");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NBANNE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("POSTE_ACTUELL"));
    return model;

        ;
}
QSqlQueryModel * Employer::rechercher(QString CIN)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM EMPLOYER WHERE CIN LIKE '%"+CIN+"%' ");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NBANNE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("POSTE_ACTUELL"));
    return model;
}
QSqlQueryModel * Employer::recherchercode(QString CIN)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT NOM FROM EMPLOYER WHERE MATRICULE='%"+CIN+"%' ");

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    return model;
}
QSqlQuery Employer::request(QString code)
{
    QSqlQuery query;
    query.prepare("select MATRICULE from EMPLOYER where MATRICULE ='"+code+"'");
    query.addBindValue(code);
    query.exec();
    return query;
}
