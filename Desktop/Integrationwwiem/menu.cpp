#include "menu.h"
#include "ui_menu.h"
#include <QMessageBox>
#include "avocat_inter.h"
#include "affaire_inter.h"
#include "gestion_des_em.h"
#include"mainwindow_citoyen.h"
#include"salle_inter.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/Zakraoui/Downloads/balsem/gestion_accuser - Copie/court backg.png");
  ui->label_2->setPixmap(pix);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_accuser_clicked()
{
    qDebug()<<"WELCOME wiem";

    wiem.show();
}
void menu::on_menu_customers_clicked()
{
   gestion_des_em *e=new gestion_des_em();
   e->show();
}

void menu::on_menu_sponsor_clicked()
{
    affaire_inter *aff = new affaire_inter();
    aff->show();

}

void menu::on_menu_missions_clicked()
{
 salle_inter *s=new salle_inter();
 s->show();
}

void menu::on_menu_transport_clicked()
{

    Avocat_inter *m = new Avocat_inter();
    m->show();

}



void menu::on_menu_missions_2_clicked()
{
    mainwindow_citoyen *c=new mainwindow_citoyen();
    c->show();
}
