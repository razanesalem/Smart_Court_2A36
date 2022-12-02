#include "menu.h"
#include "ui_menu.h"
#include <QMessageBox>
#include "avocat_inter.h"
#include "affaire_inter.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/ACER/gestion_accuser - Copie/court backg.png");
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
    QMessageBox::information(nullptr, QObject::tr("WELCOME Adem"),
                               QObject::tr("LOADING.\nClick Cancel to exit."), QMessageBox::Ok);
}

void menu::on_menu_sponsor_clicked()
{
    affaire_inter *aff = new affaire_inter();
    aff->show();

}

void menu::on_menu_missions_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("WELCOME DALI"),
                               QObject::tr("LOADING.\nClick Cancel to exit."), QMessageBox::Ok);
}

void menu::on_menu_transport_clicked()
{

    Avocat_inter *m = new Avocat_inter();
    m->show();

}


