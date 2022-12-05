#ifndef CITOYEN_H
#define CITOYEN_H
#include<QString>
#include<QSqlQuery>
#include <QDateTime>

#include <QSqlQueryModel>



class citoyen
{
public:
    //constractures

    citoyen(QString,QString,QString,QString,QString,QString,QString,QString);
    //setters
    void setnom(QString n);
    void setprenom(QString n);
    void setcin(QString n);
    void setadress(QString n);
    void setnum (QString n);
    void setemail(QString n);
    void setype(QString n);
    void setplus(QString n);
    void setnomct(QString n);
    void setprenomct(QString n);
    void setid(QString n);
    void setdate(QString n);

    //getters
    QString get_nom();
    QString get_prenom();
    QString get_cin();
    QString get_adress();
    QString get_num();
    QString get_email();
    QString get_type();
    QString get_plus();
    QString get_nomct();
    QString get_prenomct();
    QString get_date();
    //base de donner
    bool ajouter();
    bool ajoutert(QString,QString);
    QSqlQueryModel * afficher();
    bool suprimer(int);
    bool update(QString,QString,QString,QString );
    QSqlQueryModel * trier();
    QSqlQueryModel* recherche(QString ,QString );
    citoyen();
private:
    QString nom,prenom,cin,adress,num,email,type,plus,nomct,prenomct,id,date;



};

#endif // CITOYEN_H
