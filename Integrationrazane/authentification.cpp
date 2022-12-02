#include "authentification.h"
#include "ui_authentification.h"
#include <QMessageBox>
#include "QMessageBox"
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QDebug>

authentification::authentification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authentification)
{
    ui->setupUi(this);

    this->setWindowTitle("Connexion");

      QPixmap pix("C:/Users/ACER/gestion_accuser - Copie/dif.jpg");
  ui->label22->setPixmap(pix);
    ui->line_username_2->setPlaceholderText("Nom D'utilisateur");
    ui->line_password_2->setPlaceholderText("Mot de Passe");
    QTimer *timer_p=new QTimer(this);
           connect(timer_p, SIGNAL(timeout()), this,SLOT(showTime()));
           timer_p->start(1000);

}

authentification::~authentification()
{
    delete ui;
}




void authentification::showTime(){
    ui->timer_2->setText(QTime::currentTime().toString("hh:mm:ss"));

}


void authentification::on_pushButton_2_clicked()
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

                authentification::close();
                m->show();

               /* home = new class MainWindow(this);
                home->show();*/


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
