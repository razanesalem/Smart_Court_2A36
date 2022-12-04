#include "authentification.h"
#include "ui_authentification.h"
#include "mainwindow.h"
#include "connexion.h"
#include "avocat.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
Authentification::Authentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authentification)
{
    ui->setupUi(this);
}

Authentification::~Authentification()
{
    delete ui;
}


void Authentification::on_pb_conn_clicked()
{
    Authentification A( nullptr);
    Connexion  c;
    QString login;
    QString mdp;
    login=ui->le_log->text();
    mdp=ui->le_mdps->text();
    if(c.Authentification(login,mdp)==1)
    {
       QMessageBox::information(this,"Connexion","correcte");
     qDebug()<< "Mot de passe et login correct";
     this->hide();
     A.setModal(this);
     A.exec();
    }

    if(c.Authentification(login,mdp)==0)
    {
      QMessageBox::critical(this,"Connexion","incorrecte");
      qDebug()<< "Mot de passe et login incorrect";
    }
}
