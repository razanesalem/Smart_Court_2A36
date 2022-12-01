#include "menu.h"
#include "ui_menu.h"
#include <QMessageBox>
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}
void menu::on_menu_employee_clicked()
{
    qDebug()<<"WELCOME kARIM";
    khalil.show();
}

void menu::on_menu_customers_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("WELCOME WIEM"),
                               QObject::tr("LOADING.\nClick Cancel to exit."), QMessageBox::Ok);
}

void menu::on_menu_sponsor_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("WELCOME RAZANE"),
                               QObject::tr("LOADING.\nClick Cancel to exit."), QMessageBox::Ok);
}

void menu::on_menu_missions_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("WELCOME DALI"),
                               QObject::tr("LOADING.\nClick Cancel to exit."), QMessageBox::Ok);
}

void menu::on_menu_transport_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("WELCOME NOURAM"),
                               QObject::tr("LOADING.\nClick Cancel to exit."), QMessageBox::Ok);
}
