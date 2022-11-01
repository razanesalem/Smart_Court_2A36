#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QTextDocument>
#include <QSpinBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setModel(s.afficher_salle());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    int numsalle=ui->numsalle->text().toInt();

       int capacite=ui->capacite->text().toInt();
       salle s(numsalle,capacite) ;//sna3et  instance mel classe salle bel constructeur parametre

    if((numsalle==0)||(capacite==0))
    {
       QMessageBox::information(nullptr,QObject::tr("ajouter une salle"),QObject::tr("veuillez remplir les champs"),QMessageBox::Ok);
    }

     else
    {

    bool test=s.ajouter_salle();
     if(test)
    {


        QMessageBox::information(nullptr, QObject::tr("Salle ajoutée"),
                    QObject::tr("Salle ajoutée.\n"
                                "Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(s.afficher_salle());
    }

    else
     {        QMessageBox::critical(nullptr, QObject::tr("Salle non ajoutée"),
                                       QObject::tr("Salle non ajoutée .\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }
}






void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{

    int num_salle=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
        QString numsalle1=QString::number(num_salle);
        ui->numsalle->setValue(num_salle);
        int capacite=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toInt();
         QString capacite1=QString::number(capacite);
        ui->capacite->setText(capacite1);

}

void MainWindow::on_pushButton_2_clicked()
{
    int numsalle = ui->numsalle->text().toInt();
     int capacite = ui->capacite->text().toInt();

      if((numsalle==0)||(capacite==0))//||(truck_id==""))
      {
         QMessageBox::information(nullptr,QObject::tr("Ajouter une salle"),QObject::tr("Remplir les champs"),QMessageBox::Ok);
      }
      salle s;

      bool test=s.modifier_salle(numsalle,capacite);
      if(test)
      {ui->tableView->setModel(s.afficher_salle());
          QMessageBox::information(nullptr, QObject::tr("Salle modifiée"),
                      QObject::tr("Salle modfiée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
       {        QMessageBox::critical(nullptr, QObject::tr("Salle non modifiée"),
                                         QObject::tr("Salle non modifiée.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

void MainWindow::on_pushButton_3_clicked()
{
    salle s;

    int numsalle=ui->supp->text().toInt();
    //qDebug()<<numsalle;
    bool test1;
    test1=search(numsalle);
    if(test1==false)
    {

        QMessageBox::critical(nullptr, QObject::tr("salle non supprimée"),
                              QObject::tr("salle non supprime .\n"
                                          "Click Cancek to exit"), QMessageBox::Cancel);
}
    else{
        s.supprimer_salle((numsalle));
        ui->tableView->setModel(s.afficher_salle());
        QMessageBox::information(nullptr, QObject::tr("salle  supprimée"),
                              QObject::tr("salle supprime .\n"
                                          "Click Cancek to exit"), QMessageBox::Cancel);


    }
}
bool MainWindow::search(int numsalle)
{
    bool test=false;
    for(int i=0;i<ui->tableView->model()->rowCount();i++)
        if(ui->tableView->model()->index(i,0).data().toInt()==numsalle)
        {
            test=true;
        }
    return test;
}
