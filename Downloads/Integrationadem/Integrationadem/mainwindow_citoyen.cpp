#include "mainwindow_citoyen.h"
#include "ui_mainwindow_citoyen.h"
#include "qmessagebox.h"
#include "citoyen.h"
#include "connexion.h"
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QDragEnterEvent>
#include <QListWidgetItem>
#include <QMimeData>
#include <QDateTime>
#include<QSortFilterProxyModel>
#include <QPieSeries>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QColor>
#include <QSerialPort>
#include<QDebug>
#include<arduino.h>
#include <QSerialPortInfo>




mainwindow_citoyen::mainwindow_citoyen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainwindow_citoyen)



{

    ui->setupUi(this);
    ui->tableView->setModel((etmp.afficher()));

        ui->lineEdit_5->setValidator( new QIntValidator(0, 999999, this));
        ui->lineEdit_7->setValidator( new QIntValidator(0, 9999999, this));
        QDate date=QDate::currentDate();
        QString datestring=date.toString();
QTime time=QTime::currentTime();
QString timestring=time.toString();
ui->dateEdit->setDate(date);

    //QPixmap pix("C:/Users/adam/Desktop/qttry.png");
    //ui->label_pic->setPixmap(pix);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->tableView->setModel(etmp.afficher());


      QSqlQueryModel * model1=new QSqlQueryModel();
      model1->setQuery("select ID_CT from CITOYEN");
      ui->comboBox_2->setModel(model1);


      QSqlQueryModel * model2=new QSqlQueryModel();
      // model2->setQuery("select ID_CT from CITOYEN LEFT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID WHERE DATE_CT.CIT_ID=NULL");
     model2->setQuery("select ID_CT from CITOYEN");
      ui->comboBox_3->setModel(model2);


      QSqlQueryModel * model07=new QSqlQueryModel();
      //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
      model07->setQuery("select CIT_ID from DATE_CT");
      ui->comboBox_5->setModel(model07);





       /////////////////////////////////////////////



     /** int ret=A.connect_arduino(); // lancer la connexion à arduino
                       switch(ret){
                       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
                           break;
                       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                          break;
                       case(-1):qDebug() << "arduino is not available";
                       }
                        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(input())); // permet de lancer
                        //le slot update_label suite à la reception du signal readyRead (reception des données).**/




      }



mainwindow_citoyen::~mainwindow_citoyen()
{
    ui->tableView->setModel((etmp.afficher()));

    delete ui;
}





void mainwindow_citoyen::on_pushButton_4_clicked()
{
    QString test1= ui->lineEdit_5->text();
    bool num;
    int val=test1.toInt(&num);
    QString ref;
    citoyen c;
QString nom=(ui->lineEdit_3->text());
QString cin=test1;

    if(ui->lineEdit_3->text()==""){
          QMessageBox::information(this,tr("Error"),tr("SVP,remplir le nom correctement"));
    }
    else if(ui->lineEdit_4->text()==""){
        QMessageBox::information(this,tr("Error"),tr("SVP,remplir le prenom correctement"));
  }
    else if(test1==""){


        QMessageBox::critical(this,tr("Error"),tr("SVP,remplir le cin correctement"));
  }   else if(ui->lineEdit_6->text()==""){
        QMessageBox::critical(this,tr("Error"),tr("SVP,remplir le adress correctement"));
  }   else if(ui->lineEdit_7->text()==""){
        QMessageBox::critical(this,tr("Error"),tr("SVP,remplir le num tele correctement"));
  }   else if(ui->lineEdit_8->text()==""){
        QMessageBox::critical(this,tr("Error"),tr("SVP,remplir le email correctement"));
  }   else if(ui->comboBox->currentText()==""){
        QMessageBox::critical(this,tr("Error"),tr("SVP,remplir le type correctement"));
  }   else if
           ((ui->checkBox->isChecked())||(ui->checkBox_2->isChecked())||(ui->checkBox_3->isChecked())){
        QMessageBox::information(this,tr("Términer"),tr("Succes!"));
  }
    else{ QMessageBox::information(this,tr("Error"),tr("Il faut un evidance"));}
    if (num){QString ref=QString::number(val);c.setcin(ref);}else {
        QMessageBox::critical(this,tr("Error"),tr("SVP, le cin "));}



    //get lines


c.setnom(ui->lineEdit_3->text());
c.setprenom(ui->lineEdit_4->text());
c.setemail(ui->lineEdit_8->text());
c.setnum(ui->lineEdit_7->text());
c.setadress(ui->lineEdit_6->text());


c.setype(ui->comboBox->currentText());
//chek box!!!!!!!

if
(ui->checkBox->isChecked()){c.setplus("Evidence physique");}
else if (ui->checkBox_2->isChecked()){c.setplus("Evidence Numérique");}
else if (ui->checkBox_3->isChecked()){c.setplus("Témoin");}


       // ||(ui->checkBox_2->isChecked())||(ui->checkBox_3->isChecked())){c.setplus("TES");}



bool test=c.ajouter();

//refresh tab viwer

ui->tableView->setModel(etmp.afficher());

QSqlQueryModel * model1=new QSqlQueryModel();
model1->setQuery("select ID_CT from CITOYEN");
ui->comboBox_2->setModel(model1);






  QSqlQueryModel * model2=new QSqlQueryModel();
  //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
  model2->setQuery("select ID_CT from CITOYEN");

  ui->comboBox_3->setModel(model2);





  QSqlQueryModel * model07=new QSqlQueryModel();
  //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
  model07->setQuery("select CIT_ID from DATE_CT ");
  ui->comboBox_5->setModel(model07);

if(test)
{
    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr(" done.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
   { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr(" failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);




}





}


void mainwindow_citoyen::on_pushButton_6_clicked()
{
    int cin=ui->lineEdit_9->text().toInt();
    bool test=etmp.suprimer(cin);
    ui->tableView->setModel(etmp.afficher());

    QSqlQueryModel * model1=new QSqlQueryModel();
    model1->setQuery("select ID_CT from CITOYEN");
    ui->comboBox_2->setModel(model1);






      QSqlQueryModel * model2=new QSqlQueryModel();
      //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
      model2->setQuery("select ID_CT from CITOYEN");

      ui->comboBox_3->setModel(model2);





      QSqlQueryModel * model07=new QSqlQueryModel();
      //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
      model07->setQuery("select CIT_ID from DATE_CT ");
      ui->comboBox_5->setModel(model07);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr(" deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
       { QMessageBox::critical(nullptr, QObject::tr("nope"),
                    QObject::tr(" failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);




    }


}
//affiche both ways
void mainwindow_citoyen::on_pushButton_7_clicked()
{
    ui->tableView->setModel((etmp.afficher()));
    QSqlQueryModel * model1=new QSqlQueryModel();
    model1->setQuery("select ID_CT from CITOYEN");
    ui->comboBox_2->setModel(model1);






      QSqlQueryModel * model2=new QSqlQueryModel();
      //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
      model2->setQuery("select ID_CT from CITOYEN");

      ui->comboBox_3->setModel(model2);





      QSqlQueryModel * model07=new QSqlQueryModel();
      //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
      model07->setQuery("select CIT_ID from DATE_CT ");
      ui->comboBox_5->setModel(model07);

}



void mainwindow_citoyen::on_pushButton_clicked()
{
int count=0;
    QSqlQuery qury,qry;
QString reson;

QString id=ui->comboBox_5->currentText();



      qury.prepare("select * from CITOYEN where ID_CT= '"+id+ "'");
      //qry.prepare("select * from DATE_CT where CIT_ID= '"+id+ "'");
     if(qry.exec("select * from DATE_CT where CIT_ID= '"+id+"'"))
     {

         while (qry.next())
         {count++;}
         if(count==1)
            { ui->verif_label->setText("correct, l'invitation est pret");


     }

        if(count>1)
        { ui->verif_label->setText("dublicate,error dans le system");



        }
         if(count<1)
         {if(qury.exec("select * from CITOYEN where ID_CT='"+id+"'"))
             {
                 int count1=0;
                 while (qury.next())
                 {count1++;}
                 if(count1==1)
                    { ui->verif_label->setText("La tribunal du code "+id+" n'a pas du date");


             }


         }
     }}




     if(qury.exec()&&(count==1))
     {while (qury.next()) {

             //QString date=qry.value(1).toString();
             QString nom1=ui->comboBox_5->currentText();
            QString name=ui->lineEdit_2->text();

    QPdfWriter pdf("C:/Users/adam/Desktop/pdf tribunal/"+nom1+".pdf");
    QPainter painter(&pdf);
    painter.setFont(QFont("Arial", 13));
    painter.setPen(600);
    painter.drawText(100,500,"Le citoyen de code:");
    painter.drawText(100,700,id);
    painter.drawText(100,900,"Mr/Mm:");
    painter.drawText(100,1100,name);
    painter.setPen(20);
    painter.drawText(6000,500,"Greffe du tribunal de Tunisie");
    painter.drawText(6000,800,"Le juge _________ ");
    QPixmap p;
    p.load("C:/Users/adam/Desktop/qttry.png");

    painter.drawPixmap(3200,1000,3500,3000,p);
    painter.setFont(QFont("Arial", 10));
    painter.drawText(500,3500,"Madame, Monsieur le juge, ");
     painter.drawText(300,3800,"J'ai été convoqué(e) à une audience dans le cadre du litige "+id);

             QString reson = qury.value(6).toString();
     painter.drawText(300,4000,"Par la présente, sollicite le report de la date de cette audience pour les motifsuivates d'une "+reson);
     painter.drawText(300,4200,"Je vous transmets les ,stificatits à l'appui de ma demande et vous remercie par avancede votre bienveillance à mon égard.");
    //QString date=ui->dateEdit->date().toString();
    QString date=qry.value(2).toString();

     painter.drawText(300,4400,"Dans la date suivante: "+date);

     painter.setFont(QFont("Arial", 15));
     painter.drawText(100,6000,"Confirmation par signature");
     painter.drawText(6000,6000,"Cachier de confirmation");



}}else  { QMessageBox::critical(nullptr, QObject::tr("Echec"),
                                QObject::tr("L'invitation pdf na pas cree"), QMessageBox::Cancel);


                }

}

void mainwindow_citoyen::on_tableView_clicked(const QModelIndex &index)
{
     QString val=ui->tableView->model()->data(index).toString();
     QSqlQuery qury;
     qury.prepare("select  from CITOYEN where ADRESS_CT='"+val+"' or MAIL_CT='"+val+"' or NUM_CT='"+val+"' or ID_CT='"+val+"'");
     if (qury.exec())
     {while(qury.next())
             ui->lineEdit_10->setText(qury.value(3).toString());
             ui->lineEdit_11->setText(qury.value(4).toString());
             ui->lineEdit_12->setText(qury.value(5).toString());}




}


void mainwindow_citoyen::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    citoyen c;
    QString name=ui->comboBox_2->currentText();
    QSqlQuery qry;
    qry.prepare("select * from CITOYEN where ID_CT= '"+name+ "'");
    if(qry.exec())
    {while (qry.next()) {ui->lineEdit_10->setText(qry.value(3).toString());
            ui->lineEdit_11->setText(qry.value(4).toString());
            ui->lineEdit_12->setText(qry.value(5).toString());}

}
}



void mainwindow_citoyen::on_load_clicked()
{


     QString namz=ui->comboBox_3->currentText();
     QSqlQuery query,qry;
        if(query.exec("select * from DATE_CT where CIT_ID='"+namz+"'"))
        {
            int count=0;
            while (query.next())
            {count++;}
            if(count==1)
               {
                ui->listWidget->setDragEnabled(false);
                ui->listWidget->addItem(namz+", a une date specific");
                ui->comboBox_3->setItemText(ui->comboBox_3->currentIndex(),"");

        }

else  if(qry.exec("select * from CITOYEN where ID_CT='"+namz+"'")){
                ui->listWidget->setDragEnabled(true);
                ui->listWidget->addItem(namz);
                ui->comboBox_3->setItemText(ui->comboBox_3->currentIndex(),"");}}
        QSqlQueryModel * model1=new QSqlQueryModel();
        model1->setQuery("select ID_CT from CITOYEN");
        ui->comboBox_2->setModel(model1);











          QSqlQueryModel * model07=new QSqlQueryModel();
          //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
          model07->setQuery("select CIT_ID from DATE_CT ");
          ui->comboBox_5->setModel(model07);}














void mainwindow_citoyen::on_tableView_activated(const QModelIndex &index)
{
    ui->tableView->setModel(etmp.afficher());

    QSqlQueryModel * model1=new QSqlQueryModel();
    model1->setQuery("select ID_CT from CITOYEN");
    ui->comboBox_2->setModel(model1);

}

void mainwindow_citoyen::on_pushButton_8_clicked()
{
    citoyen c;
       // bool test=c.update();
        QString id=ui->comboBox_2->currentText();
        QString adres=ui->lineEdit_10->text();
        QString email=ui->lineEdit_11->text();
        QString numero=ui->lineEdit_12->text();



        bool test=c.update(id,adres,email,numero);

        ui->tableView->setModel(etmp.afficher());

        QSqlQueryModel * model1=new QSqlQueryModel();
        model1->setQuery("select ID_CT from CITOYEN");
        ui->comboBox_2->setModel(model1);






          QSqlQueryModel * model2=new QSqlQueryModel();
          //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
          model2->setQuery("select ID_CT from CITOYEN");

          ui->comboBox_3->setModel(model2);





          QSqlQueryModel * model07=new QSqlQueryModel();
          //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
          model07->setQuery("select CIT_ID from DATE_CT ");
          ui->comboBox_5->setModel(model07);
}




void mainwindow_citoyen::on_pushButton_9_clicked()
{
    citoyen c;

       //affichage simple
       ui->tableView->setModel(c.trier());

}



void mainwindow_citoyen::on_save_clicked()
{

citoyen c;

    QString id=ui->comboBox_3->currentText();

    QSqlQuery query;
        if(query.exec("select * from DATE_CT where CIT_ID='"+id+"'"))
        {
            int count=0;
            while (query.next())
            {count++;}
            if(count==1)
               {QMessageBox::information(nullptr, QObject::tr("no"),
                                         QObject::tr("error"), QMessageBox::Cancel);}
else if (count<1)
            {QString datei=ui->dateEdit->date().toString();

                QString id1=ui->comboBox_3->currentText();
                bool test=c.ajoutert(id1,datei);
                ui->listWidget_2->clear();
                QSqlQueryModel * model1=new QSqlQueryModel();
                model1->setQuery("select ID_CT from CITOYEN");
                ui->comboBox_2->setModel(model1);


                QSqlQueryModel * model2=new QSqlQueryModel();
               model2->setQuery("select ID_CT from CITOYEN");
                ui->comboBox_3->setModel(model2);


                QSqlQueryModel * model07=new QSqlQueryModel();
                model07->setQuery("select CIT_ID from DATE_CT");
                ui->comboBox_5->setModel(model07);

if(test)
                   { QMessageBox::information(nullptr, QObject::tr("done"),
                                QObject::tr("Date du tribunal a ete ajouter "), QMessageBox::Cancel);
    ui->listWidget->clear();
    ui->listWidget_2->clear();

                   }
            }

            QSqlQueryModel * model1=new QSqlQueryModel();
            model1->setQuery("select ID_CT from CITOYEN");
            ui->comboBox_2->setModel(model1);






              QSqlQueryModel * model2=new QSqlQueryModel();
              //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
              model2->setQuery("select ID_CT from CITOYEN");

              ui->comboBox_3->setModel(model2);





              QSqlQueryModel * model07=new QSqlQueryModel();
              //model2->setQuery("select ID_CT from CITOYEN RIGHT JOIN DATE_CT ON CITOYEN.ID_CT=DATE_CT.CIT_ID ");
              model07->setQuery("select CIT_ID from DATE_CT ");
              ui->comboBox_5->setModel(model07);




}}

/**void MainWindow::on_dateTimeEdit_dateChanged(const QDate &date)
{
    QSqlQuery qry;
    QDate dae=ui->dateEdit->date().currentDate();
    if (date!=dae){QString lor=dae.toString();
        if(qry.exec("select * from DATE_CT where DATE='"+lor+"'"))
            {
                int count=0;
                while (qry.next())
                {count++;}
                if(count==1)
                   { ui->listWidget_2->addItem(qry.value(0).toString());


            }}
else
                    ui->listWidget_2=new QListWidget;



    }
}**/

/**void MainWindow::on_pushButton_10_clicked()
{
    QSqlQuery query;
    QString id=ui->lineEdit->text();

    if(id!=""){
    ui->lineEdit_13->setText(id);
    ui->label_ver->setText("coller!");}
    }**/

void mainwindow_citoyen::on_pushButton_11_clicked()
{
    QString id=ui->lineEdit_13->text();
    QSqlQuery query;
        if(query.exec("select * from CITOYEN where ID_CT='"+id+"'"))
        {
            int count=0;
            while (query.next())
            {count++;}
            if(count==1)
               { ui->verif_label->setText("Trouver!");


                ui->comboBox_3->setCurrentText(id);



        }}
}


void mainwindow_citoyen::on_pushButton_12_clicked()
{
    QString variable;
                  if(ui->comboBox_4->currentText()=="ID_CT")
                  {
                   variable="ID_CT";
                  }
                  if(ui->comboBox_4->currentText()=="NOM_CT")
                  {
                   variable="NOM_CT";
                  }
                  if(ui->comboBox_4->currentText()=="PRENOM_CT")
                  {
                   variable="PRENOM_CT";
                  }
                  if(ui->comboBox_4->currentText()=="ADRESS_CT")
                  {
                   variable="ADRESS_CT";
                  }
                  if(ui->comboBox_4->currentText()=="MAIL_CT")
                  {
                   variable="MAIL_CT";
                  }
                  if(ui->comboBox_4->currentText()=="NUM_CT")
                  {
                   variable="NUM_CT";
                  }

                  citoyen I;
                  QSqlQueryModel *model =I.recherche(ui->lineEdit_9->text(),variable);
                  ui->tableView->setModel(model);
                  //ui->afficher->setModel(model);
                  ui->lineEdit_9->clear();
}



void mainwindow_citoyen::on_pushButton_13_clicked()
{
    ui->listWidget_2->clear();

    ui->listWidget->clear();
    ui->listWidget->setDragEnabled(true);
}

void mainwindow_citoyen::on_comboBox_5_currentIndexChanged(const QString &value)
{
    citoyen c;
    QString name=ui->comboBox_5->currentText();
    QSqlQuery qry,qury;
    qry.prepare("select * from CITOYEN where ID_CT= '"+name+ "'");
    qury.prepare("select * from DATE_CT where CIT_ID= '"+name+ "'");
    if(qry.exec())
    {while (qry.next()) {ui->lineEdit_2->setText(qry.value(1).toString());
         }
        if(qury.exec())
        {while (qury.next()) {ui->lineEdit->setText(qury.value(1).toString());
             }

}}



}




void mainwindow_citoyen::on_stat_raz_clicked()
{
    using namespace QtCharts;
    QSqlQueryModel * model= new QSqlQueryModel();

       model->setQuery("SELECT TYPE_CT FROM CITOYEN WHERE  TYPE_CT='A' ");
       float countA=model->rowCount();

       model->setQuery("SELECT TYPE_CT FROM CITOYEN WHERE  TYPE_CT='B' ");
       float countB=model->rowCount();
       model->setQuery("SELECT TYPE_CT FROM CITOYEN WHERE  TYPE_CT='C' ");
       float countC=model->rowCount();
       float total=countA+countB+countC;

               QPieSeries *series = new QPieSeries();
               series->append("type A",countA);
               series->append("type B",countB);
               series->append("type c",countC);

               if (countA!=0)
               {QPieSlice *slice = series->slices().at(0);
                   slice->setLabel("type A "+QString("%1%").arg(100*slice->percentage(),3,'f',1));
                   slice->setLabelVisible();
                   slice->setPen(QPen(Qt::black));}
               if ( countB!=0)
               {

                   QPieSlice *slice1 = series->slices().at(1);

                   slice1->setLabel("type B "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                   slice1->setLabelVisible();
                   slice1->setBrush(QColor(Qt::cyan));
               }
               if ( countC!=0)
               {

                   QPieSlice *slice2 = series->slices().at(2);

                   slice2->setLabel("type C "+QString("%1%").arg(100*slice2->percentage(),3,'f',1));
                   slice2->setLabelVisible();
                   slice2->setBrush(QColor(Qt::red));
               }



               // Create the chart widget
               QChart *chart = new QChart();

               // Add data to chart with title
               chart->addSeries(series);
               chart->setTitle("Totale "+ QString::number(total));

               // Used to display the chart
               QChartView *chartView = new QChartView(chart);
               chartView->setRenderHint(QPainter::Antialiasing);
               chartView->resize(1000,500);


               chart->legend()->hide();
               chartView->show();
}
/**void mainwindow_citoyen::input()
{
     data="";

qDebug() << data ;

 data=A.read_from_arduino();
  int D=data.toInt();
qDebug() << D ;
  if(A.cherchercode(D) != ""){
      A.updateRGB("g%");
  QString name = "ahla " + A.cherchercode(D);
  QMessageBox msgBox;
  msgBox.setText(name);
  msgBox.exec();
  }
  else A.updateRGB("r%");
}**/




