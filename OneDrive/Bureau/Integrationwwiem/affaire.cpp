#include "affaire.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>



//------------------------------constructeurs--------------------------------------------

Affaire::Affaire()
{
   this->NumAff=0;
   this->type="";
   this->dateinscrit="";
   this->etataf="";
   this->object="";
}



Affaire::Affaire(int NumAff,QString type,QString dateinscrit,QString etataf,QString object){
    this->NumAff=NumAff;
    this->type=type;
    this->dateinscrit=dateinscrit;
    this->etataf=etataf;
    this->object=object;
}

//----------------------------------gettersetsetters----------------------------------------
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

//--------------------------------ajout------------------------------------------

bool Affaire::ajouter(){

QSqlQuery query;

QString id= QString ::number(NumAff);

//prepare prend la requete en para pour preparer a execution

    query.prepare("INSERT INTO affaires (NUMAFF,TYPE,DATEINSCRIT,ETATAF,OBJECT) "
                  "VALUES (:NumAff,:type,:dateinscrit,:etataf,:object)");

//crr des var liées

    query.bindValue(":NumAff",id);
    query.bindValue(":type",type);
    query.bindValue(":dateinscrit",dateinscrit);
    query.bindValue(":etataf",etataf);
    query.bindValue(":object",object);



   return query.exec();  //envoie du requete pour exec

}

//----------------------------------supp----------------------------------------

bool Affaire::supprimer(int id){
    QSqlQuery query;
    QString res= QString ::number(id);
    query.prepare("Delete from affaires where NumAff= :id");
    query.bindValue(":id",res);
    return query.exec();
}

//-----------------------------------affichage---------------------------------------

QSqlQueryModel*  Affaire:: afficher()
{

QSqlQueryModel* model =new QSqlQueryModel();

model->setQuery ("select * from affaires");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMAFF"));

model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEINSCRIT"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETATAF"));
 model->setHeaderData(4,Qt::Horizontal,QObject::tr("OBJECT"));

return model;
}


//-------------------------------------modif-------------------------------------

bool Affaire::modifier(int num)
{

QSqlQuery query,rech;

QString id= QString::number(num);

query.prepare("Update affaires set TYPE=:type,DATEINSCRIT=:dateinscrit,ETATAF=:etataf,OBJECT=:object where NumAff=:NumAff ");

query.bindValue(":NumAff",id);
query.bindValue(":type",type);
query.bindValue(":dateinscrit",dateinscrit);
query.bindValue(":etataf",etataf);
query.bindValue(":object",object);

return    query.exec();
}

//-----------------------------------trie---------------------------------------

QSqlQueryModel*  Affaire:: trie()
{

QSqlQueryModel* model =new QSqlQueryModel();

model->setQuery ("select * from affaires order by NUMAFF");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMAFF"));

model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEINSCRIT"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETATAF"));
 model->setHeaderData(4,Qt::Horizontal,QObject::tr("OBJECT"));


return model;
}

//-----------------------------------recherche---------------------------------------



QSqlQueryModel* Affaire::recherche(QString test)
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery ("select * from affaires where(NUMAFF LIKE '%"+test+"%' OR TYPE LIKE '%"+test+"%' OR ETATAF LIKE '%"+test+"%' )");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMAFF"));

    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEINSCRIT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETATAF"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("OBJECT"));


    return model;
}
//-----------------------------------archive-------------------------------------------------

bool Affaire::archiver()
{
    QSqlQuery query;

    QString id= QString ::number(NumAff);

    //prepare prend la requete en para pour preparer a execution  //ajout en tab archiveaff

        query.prepare("INSERT INTO archiveaff (NUMAFF,TYPE,DATEINSCRIT,ETATAF,OBJECT) "
                      "VALUES (:NumAff,:type,:dateinscrit,:etataf,:object)");

    //crr des var liées

        query.bindValue(":NumAff",id);
        query.bindValue(":type",type);
        query.bindValue(":dateinscrit",dateinscrit);
        query.bindValue(":etataf",etataf);
        query.bindValue(":object",object);



       return query.exec();
}

//-----------------------------------desarchivage-----------------------------------


bool Affaire::desarchiver()
{
    QSqlQuery query;

    QString id= QString ::number(NumAff);

    //prepare prend la requete en para pour preparer a execution  //insrt en affaire

        query.prepare("INSERT INTO affaires (NUMAFF,TYPE,DATEINSCRIT,ETATAF,OBJECT) "
                      "VALUES (:NumAff,:type,:dateinscrit,:etataf,:object)");



        query.bindValue(":NumAff",id);
        query.bindValue(":type",type);
        query.bindValue(":dateinscrit",dateinscrit);
        query.bindValue(":etataf",etataf);
        query.bindValue(":object",object);



       return query.exec();

}

//-----------------------------------suppression colonne du table archive pour le desarchivage
bool Affaire::supparch(int id){

    QSqlQuery query;

    QString res= QString ::number(id);

    query.prepare("Delete from archiveaff where NumAff= :id");

    query.bindValue(":id",res);

    return query.exec();

}

//-----------------------------------affichage table archive

QSqlQueryModel*  Affaire:: afficher_archive()
{

QSqlQueryModel* model =new QSqlQueryModel();

model->setQuery ("select * from archiveaff");

model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMAFF"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATEINSCRIT"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETATAF"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("OBJECT"));

return model;
}




//-------------------------------------destructeur-------------------------------------


Affaire::~Affaire(){}
