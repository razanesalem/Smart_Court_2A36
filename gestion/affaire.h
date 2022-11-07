#ifndef AFFAIRE_H
#define AFFAIRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Affaire
{

private:
    int NumAff;
    QString type,dateinscrit,etataf,object;


public:
    Affaire();
    Affaire(int,QString,QString,QString,QString);
    ~Affaire();
    int getnum();
    QString gettyp();
    QString getdi();
    QString getet();
    QString getob();
    void setnum(int);
    void settyp(QString);
    void setdi(QString);
    void setet(QString);
    void setob(QString);
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel  *afficher();
    bool modifier(int);
    QSqlQueryModel * triedate();
    QSqlQueryModel *  recherchertype(QString);

};

#endif // AFFAIRE_H
