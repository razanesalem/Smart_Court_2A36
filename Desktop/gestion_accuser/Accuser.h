#ifndef ACCUSER_H
#define ACCUSER_H
#include <QString>
#include <iostream>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QtSql/QSqlQueryModel>
class Accuser

{
public:
    Accuser();
    Accuser(QString,QString,QString,QString,QString);
   //setteres
    void setnom(QString n);
    void setprenom(QString n);
    void setID(QString n);
    void setAffaire(QString n);
    void setEtat(QString n);
    //getters
    QString getnom();
    QString getprenom();
    QString getid();
    QString getaffaire();
    QString getetat();
    ~Accuser();
    //crud
    bool ajouter(Ui::MainWindow*ui);
    bool supprimer(Ui::MainWindow *ui);
    bool Modifier(Ui::MainWindow *ui);
    void AfficherTable(Ui::MainWindow *ui);


private:
    QString nom,prenom,id,affaire,etat;
};
#endif // ACCUSER_H
