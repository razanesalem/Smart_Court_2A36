#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaire.h"
#include <QString>
#include <QDateEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    Affaire A;
    //comboboxx
    ui->typeaff->setModel(A.afficher());
    ui->etataff->setModel(A.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbajouter_clicked()
{
    int id =ui->NumAff->text().toInt();
    QString ob=ui->inputobject->text();
    QString t=ui->typeaff->currentText();
    QString ef=ui->etataff->currentText();
    QString di=ui->dateTimeInscrit->text();
    Affaire A(id,t,di,ef,ob);
    bool test=A.ajouter();
    if(test)
    {
        ui->typeaff->setModel(A.afficher());
        ui->etataff->setModel(A.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



}
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("ajout non effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
