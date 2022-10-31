#include "affaire.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Affaire::Affaire()
{
   NumAff=0;
   type="";
   dateinscrit="";
   etataf="";
   object="";
}
Affaire::Affaire(int NumAff,QString type,QString dateinscrit,QString etataf,QString object){
  this->NumAff=NumAff;
    this->type=type;
    this->dateinscrit=dateinscrit;
    this->etataf=etataf;
    this->object=object;
}
Affaire::~Affaire(){}
int Affaire::getnum(){return this->NumAff;}
QString Affaire::gettyp(){return this->type;}
QString Affaire::getdi(){return this->dateinscrit;}
QString Affaire::getet(){return this->etataf;}
QString Affaire::getob(){return this->object;}
void Affaire::setnum(int NumAff){this->NumAff=NumAff;}
void Affaire::settyp(QString type){this->type=type;}
void Affaire::setdi(QString dateinscrit){this->dateinscrit=dateinscrit;}
void Affaire::setet(QString etataf){this->etataf=etataf;}
void Affaire::setob(QString object){this->object=object;}

bool Affaire::ajouter(){

QSqlQuery query;

QString id= QString ::number(NumAff);
    query.prepare("INSERT INTO affaires (NUMAFF,TYPE,DATEINSCRIT,ETATAF,OBJECT) "
                  "VALUES (:NumAff,:type,:dateinscrit,:etataf,:object)");


    query.bindValue(":NumAff",id);
    query.bindValue(":type",type);
    query.bindValue(":dateinscrit",dateinscrit);
    query.bindValue(":etataf",etataf);
    query.bindValue(":object",object);
   return query.exec();

}

QSqlQueryModel *Affaire:: afficher()
{

QSqlQueryModel * model =new QSqlQueryModel();
model->setQuery ("select * from affaire");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMAFF"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEINSCRIT"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETATAF"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("OBJECT"));
return model;

}
