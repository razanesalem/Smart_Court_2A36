#include "salle_inter.h"
#include "ui_salle_inter.h"
#include <QTextStream>
#include <QTextDocument>
#include <QSpinBox>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QTextStream>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QLabel>
#include <QtPrintSupport/QPrintDialog>
#include <QtCharts>
#include <QFile>
#include"salle.h"

salle_inter::salle_inter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::salle_inter)
{
    ui->setupUi(this);
    ui->tableView->setModel(s.afficher_salle());
    ui->tableView->setModel(s.afficher_salle());
    ui->research->setPlaceholderText(QString("Research"));
    ui->supp->setPlaceholderText(QString("Suppression"));
}

salle_inter::~salle_inter()
{
    delete ui;
}
void salle_inter::on_pushButton_clicked()
{
    int numsalle=ui->numsalle->text().toInt();

       int capacite=ui->capacite_2->text().toInt();
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






void salle_inter::on_tableView_doubleClicked(const QModelIndex &index)
{

    int num_salle=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
        QString numsalle1=QString::number(num_salle);
        ui->numsalle->setValue(num_salle);
        int capacite=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toInt();
         QString capacite1=QString::number(capacite);
        ui->capacite_2->setValue(capacite);

}

void salle_inter::on_pushButton_2_clicked()
{
    int numsalle = ui->numsalle->text().toInt();
     int capacite = ui->capacite_2->text().toInt();

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

void salle_inter::on_pushButton_3_clicked()
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
bool salle_inter::search(int numsalle)
{
    bool test=false;
    for(int i=0;i<ui->tableView->model()->rowCount();i++)
        if(ui->tableView->model()->index(i,0).data().toInt()==numsalle)
        {
            test=true;
        }
    return test;
}

void salle_inter::on_research_textChanged(const QString &arg1)
{
    QString rech=ui->research->text();
      ui->tableView->setModel(s.researchsalle(rech));
}

void salle_inter::on_pushButton_4_clicked()
{
    ui->tableView->setModel(s.view_tri_capacite());
}

void salle_inter::on_pushButton_5_clicked()
{
    QString strStream;
                         QTextStream out(&strStream);

                         const int rowCount = ui->tableView->model()->rowCount();
                         const int columnCount = ui->tableView->model()->columnCount();
                         QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                         QString DD=QDateTime::currentDateTime().toString();
                         out <<"<html>\n"
                               "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             << "<title>ERP - DELIVERIES LIST<title>\n "
                             << "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> ******LISTE DES SALLES ******"+TT+" </strong></h1>"
                             "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                               "</br> </br>";
                         // headers
                         out << "<thead><tr bgcolor=#d6e5ff>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tableView->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++) {
                                 if (!ui->tableView->isColumnHidden(column)) {
                                     QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

                         QPrinter printer;

                         QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                         if (dialog->exec() == QDialog::Accepted) {
                             document->print(&printer);
                         }

                         delete document;
}

void salle_inter::on_pushButton_6_clicked()
{
    ui->lineEdit_4->setText("PUBLIC");
    ui->lineEdit_5->setText("ACCUSE");
    ui->lineEdit_6->setText("AVOCAT");
    ui->lineEdit_7->setText("BANC DU JUGE");
}



void salle_inter::on_pushButton_7_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                             model->setQuery("select * from SALLE where CAPACITE <15 ");
                             float a=model->rowCount();
                             model->setQuery("select * from SALLE where CAPACITE between 15 and 30 ");
                             float aa=model->rowCount();
                             model->setQuery("select * from SALLE where CAPACITE >30 ");
                             float aaa=model->rowCount();
                             float total=a+aa+aaa;
                             QString d=QString("CAPACITE INFERIEUR A 15 "+QString::number((a*100)/total,'f',2)+"%" );
                             QString b=QString("CAPACITE ENTRE 15 ET 30 "+QString::number((aa*100)/total,'f',2)+"%" );
                             QString c=QString("CAPACITE SUPERIEUR A 30 "+QString::number((aaa*100)/total,'f',2)+"%" );
                             QPieSeries *series = new QPieSeries();
                             series->append(d,a);
                             series->append(b,aa);
                             series->append(c,aaa);
                     if (a!=0)
                     {QPieSlice *slice = series->slices().at(0);
                      slice->setLabelVisible();
                      slice->setPen(QPen());}
                     if (aa!=0)
                     {
                              // Add label, explode and define brush for 2nd slice
                              QPieSlice *slice1 = series->slices().at(1);
                              //slice1->setExploded();
                              slice1->setLabelVisible();
                     }
                     if(aaa!=0)
                     {
                              // Add labels to rest of slices
                              QPieSlice *slice2 = series->slices().at(2);
                              //slice1->setExploded();
                              slice2->setLabelVisible();
                     }
                             // Create the chart widget
                             QChart *chart = new QChart();
                             // Add data to chart with title and hide legend
                             chart->addSeries(series);
                             chart->setTitle("Statistiques de la capacité des salles  "+ QString::number(total));
                             chart->legend()->hide();
                             // Used to display the chart
                             QChartView *chartView = new QChartView(chart);
                             chartView->setRenderHint(QPainter::Antialiasing);
                             chartView->resize(1000,500);
                             chartView->show();
}

void salle_inter::on_research_cursorPositionChanged(int arg1, int arg2)
{

}
