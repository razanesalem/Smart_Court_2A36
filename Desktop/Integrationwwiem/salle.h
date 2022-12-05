#ifndef SALLE_H
#define SALLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class salle {
    private :
    int numsalle;
    int capacite;
public:
    salle();//constructeur par défaut
    salle(int numsalle,int capacite);//constructeur paramétré
    bool ajouter_salle();
    QSqlQueryModel *afficher_salle();
    bool modifier_salle(int,int);
    bool supprimer_salle(int);
     QSqlQueryModel * researchsalle(QString);
      QSqlQueryModel *  view_tri_capacite();
};
#endif // SALLE_H

