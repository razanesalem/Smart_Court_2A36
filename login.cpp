#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QDebug>

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





void login::on_OK_clicked()

    {

           // MainWindow m(nullptr);
            Connection  c;
            QString nom=ui->nom->text();;
            int loginn=ui->password->text().toInt();

            if(c.Authentification(loginn,nom)==1)
            {
               QMessageBox::information(this,"Connexion","login et mdp correcte");
             qDebug()<< "Mot de passe et login correct";
             this->hide();
             MainWindow* m = new MainWindow(this);
             m->show();
            }

            if(c.Authentification(loginn,nom)==0)
            {
              QMessageBox::critical(this,"Connexion","login et mdp incorrecte");
              qDebug()<< "Mot de passe et login incorrect";
            }
        }

