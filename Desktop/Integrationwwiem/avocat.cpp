#include "avocat.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

Avocat::Avocat()
{
   id_av=0;
   nom_av=" ";
   prenom_av=" ";
   mail_av=" ";
   adresse_av=" ";
   num_tel_av=0;
   nb_aff_g_av=0;
}
Avocat::Avocat(int id_av,QString nom_av,QString prenom_av,QString mail_av,QString adresse_av,int num_tel_av,int nb_aff_g_av)
{
 this->id_av=id_av;
 this->nom_av=nom_av;
 this->prenom_av=prenom_av;
 this->mail_av=mail_av;
 this->adresse_av=adresse_av;
 this->num_tel_av=num_tel_av;
 this->nb_aff_g_av=nb_aff_g_av;
}
int Avocat::getid_av(){return id_av;}
QString Avocat:: getnom(){return nom_av;}
QString Avocat::getprenom(){return prenom_av;}
QString Avocat::getMail(){return mail_av;}
QString Avocat::getAdresse(){return adresse_av;}
int Avocat::getNum_tel(){return num_tel_av;}
int Avocat::getNb_aff_g(){return nb_aff_g_av;}
void Avocat::setid_av(int id_av){this->id_av=id_av;}
void Avocat::setnom(QString nom_av){this->nom_av=nom_av;}
void Avocat::setprenom(QString prenom_av){this->prenom_av=prenom_av;}
void Avocat::setMail(QString mail_av){this->mail_av=mail_av;}
void Avocat::setAdresse(QString adresse_av){this->adresse_av=adresse_av;}
void Avocat::setNum_tel(int num_tel_av){this->num_tel_av=num_tel_av;}
void Avocat::setNb_aff_g(int nb_aff_g_av){this->nb_aff_g_av=nb_aff_g_av;}
bool Avocat::ajouter()
{

   QSqlQuery query;
    QString id_string= QString::number(id_av);
    QString num_tel_string= QString::number(num_tel_av);
    QString nb_aff_string= QString::number(nb_aff_g_av);
    query.prepare("INSERT INTO AVOCAT(ID_AV,NOM_AV,PRENOM_AV,MAIL_AV,ADRESSE_AV,NUM_TEL_AV,NB_AFF_G_AV)"
                  "VALUES(:ID_AV,:NOM_AV,:PRENOM_AV,:MAIL_AV,:ADRESSE_AV,:NUM_TEL_AV,:NB_AFF_G_AV)");
    query.bindValue(":ID_AV",id_string);
    query.bindValue(":NOM_AV",nom_av);
    query.bindValue(":PRENOM_AV",prenom_av);
    query.bindValue(":ADRESSE_AV",adresse_av);
    query.bindValue(":MAIL_AV",mail_av);
    query.bindValue(":NUM_TEL_AV",num_tel_string);
    query.bindValue(":NB_AFF_G_AV",nb_aff_string);
    return query.exec();//execution
}
bool Avocat::supprimer(int id)
{
    QSqlQuery query;

     query.prepare("DELETE FROM AVOCAT WHERE id_av=:id");
     query.bindValue(0,id);
     return query.exec();//valeur qui return soit true soit fal
}
  QSqlQueryModel* Avocat::afficher()
  {
     QSqlQueryModel* model=new  QSqlQueryModel();
     model->setQuery("SELECT* FROM avocat");
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));//ajouter headerdata ->le nom des colone de mon tableau
     model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("prénom"));
     model->setHeaderData(3,Qt::Horizontal,QObject::tr("Mail"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("Adresse"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Numéro de téléphone"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("Nombres d'affaires gagnés"));
     return model;
  }
  bool Avocat::modifier()
  {
      QSqlQuery query;
      QString id_string= QString::number(id_av);
      QString num_tel_string= QString::number(num_tel_av);
      QString nb_aff_string= QString::number(nb_aff_g_av);
      query.prepare("UPDATE AVOCAT SET NOM_AV=:NOM_AV,PRENOM_AV=:PRENOM_AV,MAIL_AV=:MAIL_AV,ADRESSE_AV=:ADRESSE_AV,NUM_TEL_AV=:NUM_TEL_AV,NB_AFF_G_AV=:NB_AFF_G_AV WHERE ID_AV=:ID_AV ");
      query.bindValue(":ID_AV",id_string);
      query.bindValue(":NOM_AV",nom_av);
      query.bindValue(":PRENOM_AV",prenom_av);
      query.bindValue(":ADRESSE_AV",adresse_av);
      query.bindValue(":MAIL_AV",mail_av);
      query.bindValue(":NUM_TEL_AV",num_tel_string);
      query.bindValue(":NB_AFF_G_AV",nb_aff_string);
      return query.exec();
  }
  QSqlQueryModel *Avocat::trier()
  {
      QSqlQueryModel * model= new QSqlQueryModel();
              model->setQuery("SELECT * FROM avocat ORDER BY ID_AV");
              return model;
  }
  QSqlQueryModel* Avocat::rechercher(QString rech)
  {
      QSqlQueryModel * model= new QSqlQueryModel();
          QString recher="select * from avocat where ID_AV like '%"+rech+"%'";
          model->setQuery(recher);
          return model;
  }


  QSqlQuery Avocat::complett()
  {QSqlQuery query;

  query.prepare("select ID_AV from avocat");

      return query;
  }


  QSqlQuery Avocat::request(QString mat)
    {
        QSqlQuery query;
        query.prepare("select nom,prenom from EMPLOYER where MATRICULE= '"+mat+"'");
        query.exec();
        return query;
    }

