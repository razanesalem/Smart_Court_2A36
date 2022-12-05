#include "gestion_des_em.h"
#include "ui_gestion_des_em.h"
#include "qmessagebox.h"
#include "connexion.h"
#include "employer.h"
#include "smtp.h"
#include "arduino.h"


#include <QIntValidator>
#include <QTableView>
#include <QMessageBox>
#include <QPixmap>
#include<QPrinter>
#include<QPainter>
#include<QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPdfWriter>

#include <QtCharts>
#include <QDesktopServices>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPieSlice>
#include <QPieSeries>
#include <QChartView>

#include <QFileDialog>
#include <QPrintDialog>
#include <QFileDialog>


gestion_des_em::gestion_des_em(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_des_em)
{
    ui->setupUi(this);
    QPixmap pix1("C:/Users/Zakraoui/Downloads/balsem/gestion_accuser/lol.jpg");
        ui->label_9->setPixmap(pix1);
        ui->label_10->setPixmap(pix1);
        ui->label_16->setPixmap(pix1);


    ui->le_CIN->setValidator( new QIntValidator(0, 999999, this));


    ui->le_nbre->setValidator( new QIntValidator(0, 36, this));
     ui->le_nom->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
     ui->le_prenom->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
      ui->tableView->setModel(E.afficher());
       ui->pb_modif->setModel(E.afficher());
        ui->le_supp->setModel(E.afficher());

        int ret=A.connect_arduino(); // lancer la connexion à arduino
                         switch(ret){
                         case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                             break;
                         case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                            break;
                         case(-1):qDebug() << "arduino is not available";
                         }
                          QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
                          //le slot update_label suite à la reception du signal readyRead (reception des données).


        }



gestion_des_em::~gestion_des_em()
{
    delete ui;
}


void gestion_des_em::on_pb_ajouter_clicked()
{
    int CIN=ui->le_CIN->text().toInt();
    int Nbanne=ui->le_nbre->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenon=ui->le_prenom->text();
     QDate date_nes=ui->dateEdit->date();
         QString poste=ui->cb_post->currentText();


Employer E(CIN,Nbanne,date_nes,nom,prenon,poste);
bool test=E.ajouter();
if(test)
{
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectue\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    //mise à jour de la table des donnée

    ui->pb_modif->setModel(E.afficher());
     ui->le_supp->setModel(E.afficher());
            ui->tableView->setModel(E.afficher());
            ui->le_CIN->clear();
             ui->le_nbre->clear();
              ui->le_nom->clear();
               ui->le_prenom->clear();


}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectue.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}


void gestion_des_em::on_pb_modifier_clicked()
{
    int CIN=ui->le_CIN->text().toInt();
    int Nbanne=ui->le_nbre->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenon=ui->le_prenom->text();
    QDate date_nes=ui->dateEdit->date();
    QString poste=ui->cb_post->currentText();


     Employer E(CIN,Nbanne,date_nes,nom,prenon,poste);

      bool test=E.modifier();

      if(test)
      {

    ui->tableView->setModel(E.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Modification effectue.\n"
                                                                          "Click Cancel to exit."), QMessageBox::Cancel);
          ui->pb_modif->setModel(E.afficher());
           ui->le_supp->setModel(E.afficher());
          ui->le_CIN->clear();
           ui->le_nbre->clear();
            ui->le_nom->clear();
             ui->le_prenom->clear();

      }
      else
      {
          QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Modification non effectue.\n"
                                                                          "Click Cancel to exit."),QMessageBox::Cancel);
      }
}

void gestion_des_em::on_pb_modif_currentIndexChanged(int index)
{

    int CIN=ui->pb_modif->currentIndex();
    QString CIN_string=QString::number(CIN);
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYER where CIN='"+CIN_string+"'");
    if(query.exec())
    {
        while (query.next())
        {
          ui->le_CIN->setText(query.value(1).toString()) ;
          ui->le_nbre->setText(query.value(2).toString()) ;
          ui->dateEdit->setDate(query.value(3).toDate()) ;
          ui->le_nom->setText(query.value(4).toString()) ;
          ui->le_prenom->setText(query.value(5).toString()) ;
          // ui->cb_post->setText(query.value(5).toString());
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                    QObject::tr("Echec.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void gestion_des_em::on_pb_supprimer_clicked()
{

        int CIN=ui->le_supp->currentText().toInt();
        bool test=E.supprimer(CIN);
        if(test)
        {

            QMessageBox::information(nullptr,QObject::tr("Suppression d'un Employe"),
                                     QObject::tr("Suppression effectuée\n" "Click Cancel to quit"),
                                     QMessageBox::Cancel);
            ui->tableView->setModel(E.afficher());

            ui->pb_modif->setModel(E.afficher());
             ui->le_supp->setModel(E.afficher());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Suppression d'un invité"),
                                  QObject::tr("Suppression non effectuée\n" "Click Cancel to quit"),
                                  QMessageBox::Cancel);

    }



void gestion_des_em::on_comboBox_tri_currentIndexChanged(const QString &arg1)
{
    QString crit=ui->comboBox_tri->currentText();
    if(crit=="Annee d'experence")
    {
      ui->tableView->setModel(E.afficher_EM_trie_Nbanne());
    }
    else if (crit=="Date naissance")
    {
      ui->tableView->setModel(E.afficher_EM_trie_date());
    }

}
QString currDate()
{
    QDate date = QDate::currentDate();
    return date.toString("dd.MM.yyyy");
}
void gestion_des_em::on_pb_pdf_clicked()
{

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("C:/Users/user/Desktop/pdf/emplyer.pdf");

    QPainter painter(&printer);
    painter.drawPixmap(QRect(100,200,2500,2500),QPixmap("C:/Users/user/Desktop/pdf/valence.png"));
    int i = 4000;
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 40));
    painter.drawText(3050,1400,"Liste des employers");
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20));
    painter.drawRect(2700,200,6500,2000);
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Arial",10));
    painter.drawText(350,3300,"CIN");
    painter.drawText(1000,3300,"Nombre d'années d'expertise");
    painter.drawText(3800,3300,"Date naissance");
    painter.drawText(6000,3300,"Nom");
    painter.drawText(7300,3300,"Prénom");
     painter.drawText(9000,3300,"Poste");

    QString date= currDate() ;
    painter.drawText(8500,30,date);

    QSqlQuery query;
    query.prepare("select * from EMPLOYER  ");
    query.exec();
    while (query.next())
    {
        painter.drawText(200,i,query.value(0).toString());
        painter.drawText(1900,i,query.value(1).toString());
        painter.drawText(3500,i,query.value(2).toString());
        painter.drawText(5900,i,query.value(3).toString());
        painter.drawText(7300,i,query.value(4).toString());
        painter.drawText(9000,i,query.value(5).toString());

        i = i + 500;
    }

    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/user/Desktop/pdf/emplyer.pdf"));

        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}
void gestion_des_em::on_lineEdit_cherche_cin_textChanged(const QString &arg1)
{
    ui->lineEdit_cherche_cin->setValidator( new QIntValidator(0, 999999, this));
    if(ui->lineEdit_cherche_cin->text()!="")
    {
      QString CIN=ui->lineEdit_cherche_cin->text();
      ui->tableView->setModel(E.rechercher(CIN));
    }
    else
     ui->tableView->setModel(E.afficher());
}
void gestion_des_em::on_pushButton_imprimer_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0,"Open File",QString(),"PDF File(*.pdf)");

    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);

    if(dlg->exec() == QDialog::Accepted)
    {
        QImage pdf(fileName);
        QPainter painter(&printer);
        painter.drawImage(QPoint(0,0),pdf);
        painter.end();
    }

    delete dlg;
}
void gestion_des_em::on_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("select * from EMPLOYER where NBANNE >= 20");
       float dispo1=model->rowCount();

       model->setQuery("select * from EMPLOYER where NBANNE <= 20");
       float dispo=model->rowCount();

       float total=dispo1+dispo;
           QString a=QString("année d'experence plus de 20 ans ," +QString::number((dispo1*100)/total,'f',2)+"%" );
           QString b=QString("année d'experence infereur de 20 ans  ,"+QString::number((dispo*100)/total,'f',2)+"%" );
           QPieSeries *series = new QPieSeries();
           series->append(a,dispo1);
           series->append(b,dispo);
       if (dispo1!=0)
       {QPieSlice *slice = series->slices().at(0);
           slice->setLabelVisible();
           slice->setPen(QPen());}
       if ( dispo!=0)
       {
           QPieSlice *slice1 = series->slices().at(1);
           slice1->setLabelVisible();
       }

       QChart *chart = new QChart();


       chart->addSeries(series);
       chart->setTitle("Années d'experience :Nombre d'employes: "+ QString::number(total));



       QChartView *chartView = new QChartView(chart);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->resize(1000,500);
       chartView->show();

}
void gestion_des_em::on_pushButton_envoyer_clicked()
{
    Smtp* smtp = new Smtp("abdelkarim.arouchi@esprit.tn", "211JMT2854", "smtp.gmail.com", 465);


        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


        QString a=ui->LE_Destinataire->text();


        QString b=ui->LE_Objet->text();


        QString c=ui->msq->text();




        smtp->sendMail("abdelkarim.arouchi@esprit.tn",a,b,c);
}
