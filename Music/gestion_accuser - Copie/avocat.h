#ifndef AVOCAT_H
#define AVOCAT_H
#include <QString>
#include <QSqlQueryModel>

class Avocat
{
    public:
    //constructeurs
    Avocat();
    Avocat(int,QString,QString,QString,QString,int,int);
    int getCIN();
    //getters
    int getid_av();
    QString getnom();
    QString getprenom();
    QString getAdresse();
    QString getMail();
    int  getNum_tel();
    int getNb_aff_g();
    //setters
    void setid_av(int);
    void setnom(QString);
    void setprenom(QString);
    void setAdresse(QString);
    void setMail(QString);
    void setNum_tel(int);
    void setNb_aff_g(int);
    ////
    bool ajouter();
    QSqlQueryModel* afficher();//resulter d'un ensemble est de type QSqlquerymodel "modele de requete de type sql"
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel *trier();
     QSqlQueryModel*rechercher(QString a);

     QSqlQuery complett();

private:
    int id_av;
    QString nom_av,prenom_av,adresse_av,mail_av;
    int num_tel_av,nb_aff_g_av;
};
#endif // AVOCAT_H
