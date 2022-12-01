#include "authentification.h"
#include "ui_authentification.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "QMessageBox"
#include <QTimer>
#include <QTime>
#include <QDateTime>
authentification::authentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authentification)
{
    ui->setupUi(this);
       setWindowTitle("LOGIN");
}

authentification::~authentification()
{
    delete ui;
}

void authentification::on_pushButton_clicked()
{
    QString username,password;
        username=ui->line_username_2->text();
        password=ui->line_password_2->text();

        QSqlQuery qry;
        if(qry.exec("select * from USER1 where ADMIN= '"+username +"' and MDP= '"+password+"'"))
        {
            int count=0;
            while(qry.next())
            {
                count++;
            }
            if (count==1)
            {   QMessageBox::information(nullptr, QObject::tr("Connected"),
                                     QObject::tr("Connexion réussite\n""Click Cancel to exit")
                                     ,QMessageBox::Cancel);
                hide();
                home = new class MainWindow(this);
                home->show();


            }
            if (count>1)
                QMessageBox::warning(nullptr, QObject::tr("Duplicated"),
                             QObject::tr("Duplication\n""Click Cancel to exit")
                             ,QMessageBox::Cancel);
            if (count<1)
                QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Nom d'utilisateur ou mot de passe incorrecte\n""Click Cancel to exit")
                             ,QMessageBox::Cancel);
        }
            }
void authentification::showTime(){
    ui->timer_2->setText(QTime::currentTime().toString("hh:mm:ss"));

}

