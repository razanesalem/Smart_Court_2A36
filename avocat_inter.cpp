#include "avocat_inter.h"
#include "ui_avocat_inter.h"
#include "avocat.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QTextDocument>
#include <QSqlDatabase>
#include "arduino.h"
Avocat_inter::Avocat_inter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Avocat_inter)
{
    ui->setupUi(this);
    ui->le_id_av->setValidator(new QIntValidator(0,99999999,this));//elle permet d'ecrire que des chiffre
    ui->le_num_tel_av->setValidator(new QIntValidator(0,99999999,this));
    ui->le_nb_aff_g_av->setValidator(new QIntValidator(0,99999999,this));
    //ui->le_nom_av->setValidator(new QRegExpValidator(QRegExp("[A-Z]*")));
    ui->tab_avocat->setModel(A.afficher());
    int ret=R.connect_arduino(); // lancer la connexion à arduino
                             switch(ret){
                             case(0):qDebug()<< "arduino is available and connected to : "<< R.getarduino_port_name();
                                 break;
                             case(1):qDebug() << "arduino is available but not connected to :" <<R.getarduino_port_name();
                                break;
                             case(-1):qDebug() << "arduino is not available";
                             }
                              QObject::connect(R.getserial(),SIGNAL(readyRead()),this,SLOT(scanne())); // permet de lancer
                              //le slot update_label suite à la reception du signal readyRead (reception des données).


CompleteID();

}

Avocat_inter::~Avocat_inter()
{
    delete ui;
}

void Avocat_inter::CompleteID()
{
    QStringList CompletionList;
    QSqlQuery qry=tempavocat.complett();

    if(qry.exec())
    {
        while(qry.next())
        {
                 CompletionList << qry.value(0).toString();
        }
    }
    StringCompliter = new QCompleter(CompletionList,this);
    StringCompliter->setCaseSensitivity(Qt::CaseSensitive);
    ui->le_id_supp->setCompleter(StringCompliter);




}


void Avocat_inter::on_pb_modifier_clicked()
{
    int id_av=ui->le_id_av->text().toInt();
        QString nom_av=ui->le_nom_av->text();
        QString prenom_av=ui->le_prenom_av->text();
        QString adresse_av=ui->le_adresse_av->text();
        QString mail_av=ui->le_mail_av_2->text();
        int num_tel_av=ui->le_num_tel_av->text().toInt();
        int nb_aff_g_av=ui->le_nb_aff_g_av->text().toInt();
        Avocat A2 (id_av,nom_av,prenom_av,adresse_av,mail_av,num_tel_av,nb_aff_g_av);
        bool test=A2.modifier();
        if(test){
  ui->tab_avocat->setModel(A2.afficher());
  CompleteID();
  QMessageBox::information(nullptr,"modification activite","activite modifie avec succés");
      }
      else
              QMessageBox::warning(nullptr,"Error","activite non modifie");


      ui->le_id_av->clear();
      ui->le_nom_av->clear();
      ui->le_prenom_av->clear();
      ui->le_adresse_av->clear();
      ui->le_mail_av_2->clear();
      ui->le_num_tel_av->clear();
      ui->le_nb_aff_g_av->clear();

}

void Avocat_inter::on_pb_ajouter_clicked()
{
    int id_av=ui->le_id_av->text().toInt();
    QString nom_av=ui->le_nom_av->text();
    QString prenom_av=ui->le_prenom_av->text();
    QString mail_av=ui->le_mail_av_2->text();
    QString adresse_av=ui->le_adresse_av->text();
    int num_tel_av=ui->le_num_tel_av->text().toInt();
    int nb_aff_g_av=ui->le_nb_aff_g_av->text().toInt();

     Avocat A(id_av, nom_av, prenom_av,adresse_av,mail_av,num_tel_av,nb_aff_g_av);
     bool test=A.ajouter();
     if(test)
     {
         QMessageBox:: information (nullptr, QObject::tr("ajout avec succes \n"),
                     QObject::tr("add successful.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tab_avocat->setModel(A.afficher());
        CompleteID();
 }
     else
         QMessageBox::critical (nullptr, QObject::tr("erreur d'ajout"),
                     QObject::tr("ajout non effectué.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}

void Avocat_inter::on_pb_supprimer_clicked()
{
    Avocat A1;
    A1.setid_av(ui->le_id_supp->text().toInt());
    bool test=A1.supprimer(A1.getid_av());
    if(test)
    {
        QMessageBox:: information (nullptr, QObject::tr("suppression avec succes \n"),
                    QObject::tr("delete successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_avocat->setModel(A.afficher());
        CompleteID();

}
    else
        QMessageBox::critical (nullptr, QObject::tr("erreur de supprission"),
                    QObject::tr("suppression non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void Avocat_inter::on_pb_stat_clicked()
{
    s = new stat_nb();
       s->setWindowTitle("statistique nombres d'affaires gagnés des avocats");
       s->stats();
       s->show();

}

void Avocat_inter::on_pb_pdf_clicked()
{
    QString strStream;
                           QTextStream out(&strStream);
                           const int rowCount = ui->tab_avocat->model()->rowCount();
                           const int columnCount =ui->tab_avocat->model()->columnCount();


                           out <<  "<html>\n"
                                   "<head>\n"
                                   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                   <<  QString("<title>%1</title>\n").arg("eleve")
                                   <<  "</head>\n"
                                   "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                       "<h1>Liste des Avocas</h1>"

                                       "<table border=1 cellspacing=0 cellpadding=2>\n";

                           // headers
                               out << "<thead><tr bgcolor=#f0f0f0>";
                               for (int column = 0; column < columnCount; column++)
                                   if (!ui->tab_avocat->isColumnHidden(column))
                                       out << QString("<th>%1</th>").arg(ui->tab_avocat->model()->headerData(column, Qt::Horizontal).toString());
                               out << "</tr></thead>\n";
                               // data table
                                  for (int row = 0; row < rowCount; row++) {
                                      out << "<tr>";
                                      for (int column = 0; column < columnCount; column++) {
                                          if (!ui->tab_avocat->isColumnHidden(column)) {
                                              QString data = ui->tab_avocat->model()->data(ui->tab_avocat->model()->index(row, column)).toString().simplified();
                                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                          }
                                      }
                                      out << "</tr>\n";
                                  }
                                  out <<  "</table>\n"
                                      "</body>\n"
                                      "</html>\n";



                   QTextDocument *document = new QTextDocument();
                   document->setHtml(strStream);


                   //QTextDocument document;
                   //document.setHtml(html);
                   QPrinter printer(QPrinter::PrinterResolution);
                   printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setOutputFileName("Avocat.pdf");
                   document->print(&printer);
}

void Avocat_inter::on_pb_trier_clicked()
{
    Avocat a;
    ui->tab_avocat->setModel(tempavocat.trier());

}

void Avocat_inter::scanne()
{

data = R.read_from_arduino();

c+=data;
qDebug()<<c;

if(c.length()==11)
{
    if(c=="08 22 5C 4B")
    {
        R.write_to_arduino("nouram");
    }

    c="";
}

    /*
while(R.getserial()->canReadLine())
   {
       data=R.getserial()->readLine();
       data.chop(2);
       qDebug()<<"Data Received: " <<data;}
        if (data == "70 9A 03 28")
        {
         int send;
                send = R.write_to_arduino("1");
        }
        ;
*/
}



void Avocat_inter::on_le_id_cher_cursorPositionChanged(int arg1, int arg2)
{
    ui->tab_avocat->setModel(tempavocat.rechercher(ui->le_id_cher->text()));

    QString test =ui->le_id_cher->text();

    if(test=="")
    {
        ui->tab_avocat->setModel(tempavocat.afficher());//refresh
    }


}
