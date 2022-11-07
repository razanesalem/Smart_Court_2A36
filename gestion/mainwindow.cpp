#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaire.h"
#include "connection.h"
#include <QString>
#include <QDateEdit>
#include <QMessageBox>
#include <QIntValidator>
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Affaire A;
    ui->tableView->setModel(A.afficher());
    ui->lNum->setValidator(new QIntValidator(1,999999, this));
    ui->comboBoxS->setModel(A.afficher());
    ui->comboBoxM->setModel(A.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()   //ajout
{
    int id=ui->lNum->text().toInt();
  //**********************************************
   /* QSqlQueryModel *modal =new QSqlQueryModel();
       QSqlQuery query;

           query.prepare("select TYPE from affaires");
       if (query.exec())
       {

              ui->comboBoxAT->setModel(modal);
       }*/
   QString t=ui->ltyp->text();


  //**********************************************
    QString di=ui->dateEditA->text();
    QString ef;
            bool e=ui->radioButtonA1->isChecked();
            if (e)
            { ef="en cours";
            }
            else ef="cloture";

    QString ob=ui->lob->text();

    Affaire A(id,t,di,ef,ob);

    bool test=A.ajouter();

    if(test)  //si requete est exec
    {

        //refresh

        ui->tableView->setModel(A.afficher());

        QMessageBox::information(nullptr, QObject::tr("success"),
                    QObject::tr("ajout effectué\n"), QMessageBox::Save);

        ui->comboBoxM->setModel(A.afficher());
        ui->comboBoxS->setModel(A.afficher());
        ui->lob->clear();
        ui->ltyp->clear();
        ui->lNum->clear();

   }
    else
        QMessageBox::critical(nullptr, QObject::tr("error"),
                    QObject::tr("ajout non effectué\n"
                                ), QMessageBox::Cancel);

}




void MainWindow::on_pushButton_2_clicked()  //supp
{
    int id=ui->comboBoxS->currentText().toInt();


    bool test=A.supprimer(id);
    if(test)
    {
        //refresh

        ui->tableView->setModel(A.afficher());

        QMessageBox::information(nullptr, QObject::tr("sucess"),
                              QObject::tr("suppression effectué\n"
                                          ), QMessageBox::Ok);
        ui->comboBoxM->setModel(A.afficher());
        ui->comboBoxS->setModel(A.afficher());


     }
              else
                  QMessageBox::critical(nullptr, QObject::tr("error"),
                              QObject::tr("suppression non effectué\n"
                                          ""), QMessageBox::Cancel);

 }



void MainWindow::on_pushButton_3_clicked()   //modif
{
    int id=ui->comboBoxM->currentText().toInt();

    QString t=ui->lineEdit_3->text();
    QString di=ui->dateEditM->text();
    QString ef;
            bool e=ui->radioButtonME->isChecked();
            if (e)
            { ef="en cours";
            }
            else ef="cloture";
    QString ob=ui->lineEdit_6->text();

    Affaire Am(id,t,di,ef,ob); //int NumAff,QString type,QString dateinscrit,QString etataf,QString object

    bool test=Am.modifier(id);

          if(test)
        {
              ui->comboBoxM->setModel(Am.afficher());
              ui->tableView->setModel(Am.afficher());
              ui->comboBoxS->setModel(Am.afficher());

        QMessageBox::information(nullptr, QObject::tr("modifier une affaire"),
                          QObject::tr("affaire modifiée.\n"
                                      ""), QMessageBox::Ok);
             ui->comboBoxS->setModel(Am.afficher());

        ui->comboBoxM->setModel(Am.afficher());
        ui->lineEdit_3->clear();
        ui->lineEdit_6->clear();
        }
          else  QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                                       QObject::tr("ERREUR.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
    }









void MainWindow::on_radioButtontridate_clicked()
{
    ui->tableView->setModel(A.triedate());
}

void MainWindow::on_pushButtontri_clicked()
{
    ui->tableView->setModel(A.afficher());
}

void MainWindow::on_PDF_clicked()
{
        QPrinter printer;


       int id=ui->lNum->text().toInt();
       QString num= QString ::number(id);

       QString t=ui->ltyp->text();

        QString di=ui->dateEditA->text();

        QString ef;
                bool e=ui->radioButtonA1->isChecked();
                if (e)
                { ef="en cours";
                }
                else ef="cloture";

        QString ob=ui->lob->text();

              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName("C:/Users/razan/OneDrive/Desktop/test.pdf");
              QPainter painter;
              if (! painter.begin(&printer))
              { // failed to open file
                  qWarning("failed to open file, is it writable?");

              }


              painter.setPen(Qt::red);
              painter.drawText(10, 10, "NUMAFF: ");
              painter.setPen(Qt::black);
              painter.drawText(70, 10, num);
              painter.setPen(Qt::red);
              painter.drawText(10, 20, "TYPE : ");
              painter.setPen(Qt::black);
              painter.drawText(70, 20, t);
              painter.setPen(Qt::red);
              painter.drawText(10, 30, "ETAT: ");
              painter.setPen(Qt::black);
              painter.drawText(70, 30, ef);
              painter.setPen(Qt::red);
              painter.drawText(10, 40, "OBJET: ");
              painter.setPen(Qt::black);
              painter.drawText(70, 40, ob);
              painter.setPen(Qt::red);
              painter.drawText(10,50,"DateInscrit:");
              painter.setPen(Qt::black);
              painter.drawText(70,50, di);


              QMessageBox::information(nullptr,QObject::tr("GENERATION PDF"),QObject::tr("PDF CREATED\n" "Click Cancel to quit"),QMessageBox::Cancel);

              if (! printer.newPage())

              {
                  qWarning("failed in flushing page to disk, disk full?");
                  painter.drawText(10, 10, "Test 2");
                  QMessageBox::critical(nullptr,QObject::tr("GENERATION PDF"),QObject::tr("PDF NOT CREATED\n" "Click Cancel to quit"),QMessageBox::Cancel);
              }


              painter.end();


}

