#include "login.h"
#include "ui_login.h"
#include "connexion.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQuery>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pb_conn_clicked()
{
    home h(nullptr);
    Connexion  c;
    QString login;
    QString mdp;
    login=ui->log->text();
    mdp=ui->mdps->text();
    if(c.Login(login,mdp)==1)
    {
       QMessageBox::information(this,"Connexion","correcte");
     qDebug()<< "Mot de passe et login correct";
     this->hide();
     h.setModal(this);
     h.exec();
    }

    if(c.login(login,mdp)==0)
    {
      QMessageBox::critical(this,"Connexion","incorrecte");
      qDebug()<< "Mot de passe et login incorrect";
    }
    }
}
