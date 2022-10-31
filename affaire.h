#ifndef AFFAIRE_H
#define AFFAIRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Affaire
{
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
    QSqlQueryModel  *afficher();
    bool ajouter();
private:
    int NumAff;
    QString type,dateinscrit,etataf,object;

};

#endif // AFFAIRE_H
