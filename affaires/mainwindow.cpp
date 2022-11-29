#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaire.h"
#include <QString>
#include <QDateEdit>
#include <QMessageBox>
#include <QIntValidator>
#include <QPainter>
#include <QPrinter>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QColor>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QString>
#include <QList>
#include <QStringList>
#include <QListIterator>
#include <QMessageBox>
#include <QRegExp>
#include <QFont>
#include "arduino.h"


#include "qrcode.h"
#include <QtSvg/QSvgRenderer>
#include <fstream>
#include <QPainter>

using qrcodegen::QrCode;
using qrcodegen::QrSegment;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Affaire A;
    ui->tableView->setModel(A.afficher());
    ui->tableView_archive->setModel(A.afficher_archive());
    ui->lNum->setValidator(new QIntValidator(1,999999, this));
    ui->comboBoxS->setModel(A.afficher());
    ui->comboBoxM->setModel(A.afficher());


    //arduino
    int ret=a.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" << a.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
    connect(a.getserial(), SIGNAL(readyRead()), this, SLOT(readArduino()));

    ui->disconnectButton->setEnabled(false);
    // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).
    }





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()   //ajout //+controle archive
{
    int num=ui->lNum->text().toInt();

    QString t=ui->ltyp->text();
    QString di=ui->dateEditA->text();
    QString ef;
            bool e=ui->radioButtonA1->isChecked();
            if (e)
            { ef="en cours";
            }
            else ef="cloture";

    QString ob=ui->lob->text();

    //+controle archive

    int found = 0;
    QString res = QString::number(num);
    QSqlQuery q;
    q.prepare("select numaff FROM archiveaff WHERE numaff = :num");
    q.bindValue(":num",res);
    q.exec();
    while (q.next()) {

        found++;

    }

    Affaire A(num,t,di,ef,ob);
    QMessageBox msgBox;
if(found==0)
{
    bool test=A.ajouter();


       if(test)
          { QMessageBox::information(nullptr, QObject::tr("success"),
                                     QObject::tr("ajout effectué\n"), QMessageBox::Save);

           ui->tableView->setModel(A.afficher());
           ui->comboBoxM->setModel(A.afficher());
                   ui->comboBoxS->setModel(A.afficher());
                   ui->lob->clear();
                   ui->ltyp->clear();
                   ui->lNum->clear();
       }
       else{
           QMessageBox::critical(nullptr, QObject::tr("error"),
                               QObject::tr("ajout non effectué\n"
                                           ), QMessageBox::Cancel);


                   ui->lob->clear();
                   ui->ltyp->clear();
                   ui->lNum->clear();}
    }
else{QMessageBox::critical(nullptr, QObject::tr("error"),
                           QObject::tr("ajout non effectué\n element archivee"
                                       ), QMessageBox::Cancel);

            ui->lob->clear();
            ui->ltyp->clear();
            ui->lNum->clear();
   }

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







//--------------------------------------------------------------------------trie

void MainWindow::on_radioButtontridate_clicked()
{
    ui->tableView->setModel(A.trie());
}

void MainWindow::on_pushButtontri_clicked()
{
 ui->tableView->setModel(A.afficher());
}


//----------------------------------------------------------------------------pdf
void MainWindow::on_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/razan/OneDrive/Desktop/affaires.pdf");
            QPainter painter(&pdf);
            int i = 4000;
            painter.setPen(Qt::blue);
            painter.setFont(QFont("Arial", 30));
            painter.drawText(3300,1200,"Liste Des affaires");
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 50));
            painter.drawRect(1500,200,7300,2600);
            painter.drawRect(0,3000,9600,500);
            painter.setFont(QFont("Arial", 9));
            painter.drawText(1300,3300,"NUM_A");
            painter.drawText(2600,3300,"TYPE");
            painter.drawText(3900,3300,"DATEINSCRIT");
            painter.drawText(5200,3300,"ETAT");
            painter.drawText(6500,3300,"OBJECT");





            QSqlQuery query;
            query.prepare("select * from AFFAIRES");
            query.exec();
            while (query.next())
            {
                painter.drawText(1300,i,query.value(0).toString());
                painter.drawText(2600,i,query.value(1).toString());
                painter.drawText(3900,i,query.value(2).toString());
                painter.drawText(5200,i,query.value(3).toString());
                painter.drawText(6500,i,query.value(4).toString());




                i = i +500;
            }

            int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/razan/OneDrive/Desktop/affaires.pdf"));

                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                painter.end();
            }


}

//-------------------------------------------------------------archivage

void MainWindow::on_pushButton_archiver_raz_clicked()
{
    int numAFF=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    QString type=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString();
    QString date=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString();
    QString etat=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString();
    QString object=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString();


    Affaire A (numAFF, type, date,etat,object);



   QMessageBox msgBox;
   if ( etat != "cloture")
   {
       msgBox.setText("Ce dossier est en cours, il ne peut pas être archivé ");

   }
   else
   {
       bool test = A.archiver();


            if (test)
            {
                bool test2 = A.supprimer(numAFF);
                if(test2)
                {
                msgBox.setText(" dossier archivé avec succes ");
                ui->tableView->setModel(A.afficher());
                ui->tableView_archive->setModel(A.afficher_archive());
                }
            }
            else
                {
                    msgBox.setText(" echec de l'archivage ");
                }
            }
   msgBox.exec();
}

//-------------------------------------------------statistique

void MainWindow::on_stat_raz_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT etataf FROM affaires WHERE  etataf='cloture' ");
    float countC=model->rowCount();

    model->setQuery("SELECT etataf FROM affaires WHERE  etataf='en cours' ");
    float countEC=model->rowCount();

    float total=countC+countEC;

            QPieSeries *series = new QPieSeries();
            series->append("cloture",countC);
            series->append("en cours",countEC);

            if (countC!=0)
            {QPieSlice *slice = series->slices().at(0);
                slice->setLabel("cloture "+QString("%1%").arg(100*slice->percentage(),3,'f',1));
                slice->setLabelVisible();
                slice->setPen(QPen(Qt::black));}
            if ( countEC!=0)
            {

                QPieSlice *slice1 = series->slices().at(1);

                slice1->setLabel("en coure "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                slice1->setLabelVisible();
                slice1->setBrush(QColor(Qt::cyan));
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

//----------------------------------------------------desearchivage
void MainWindow::on_desearchive_raz_clicked()
{
    int numAFF=ui->tableView_archive->model()->data(ui->tableView_archive->model()->index(ui->tableView_archive->currentIndex().row(),0)).toInt();
    QString type=ui->tableView_archive->model()->data(ui->tableView_archive->model()->index(ui->tableView_archive->currentIndex().row(),1)).toString();
    QString date=ui->tableView_archive->model()->data(ui->tableView_archive->model()->index(ui->tableView_archive->currentIndex().row(),2)).toString();
    QString etat=ui->tableView_archive->model()->data(ui->tableView_archive->model()->index(ui->tableView_archive->currentIndex().row(),3)).toString();
    QString object=ui->tableView_archive->model()->data(ui->tableView_archive->model()->index(ui->tableView_archive->currentIndex().row(),4)).toString();


    Affaire A (numAFF, type, date,etat,object);



   QMessageBox msgBox;

       bool test = A.desarchiver();


            if (test)
            {
                bool test2 = A.supparch(numAFF);
                if(test2){
                msgBox.setText(" dossier desarchivé avec succes ");
                ui->tableView->setModel(A.afficher());
                ui->tableView_archive->setModel(A.afficher_archive());}
            }
            else
                {
                    msgBox.setText(" echec de desarchivage ");
                }

   msgBox.exec();

}

//--------------------------------------------------------qrcode
void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox msgBox;

    QString id =ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QString type=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString();
    QString date=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString();
    QString etat=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString();
    QString object=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString();
    if (id == "")
    {
        msgBox.setText("veuillez choisir une affaire! ");
         msgBox.exec();

    }
    else {

    QString reference = id +" | "+type+" | "+date+" | "+etat+" | "+object;
    QByteArray ba = reference.toLocal8Bit();
    const char *c_str2 = ba.data();
    const QrCode qr = QrCode::encodeText(c_str2, QrCode::Ecc::LOW);
    std::ofstream myfile;
    myfile.open ("qrcode.svg");
    myfile << qr.toSvgString(1);
    myfile.close();
    QSvgRenderer svgRenderer(QString("qrcode.svg"));
    QPixmap pix( QSize(120, 120) );
    QPainter pixPainter( &pix );
    svgRenderer.render( &pixPainter );
    ui->label_Qrcode->setPixmap(pix);
    ui->label_Qrcode->hasFocus();
    }
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableView->setModel(A.recherche(arg1));
}

//----------------------------------------------------arduino
/*
void MainWindow::on_comportComboBox_currentIndexChanged(const QString &arg1)
{
    a.setarduino_port_name(arg1);
    qDebug() << a.getarduino_port_name();
}

void MainWindow::on_baudRateComboBox_currentIndexChanged(const QString &arg1)
{
    a.setcurrentBaudRate((qint32)arg1).toInt();
    qDebug() << a.currentBaudRate;

}

void MainWindow::on_baudRateComboBox_currentIndexChanged(int index)
{
    a.setcurrentBaudRate(index);
    qDebug() << a.getcurrentBaudRate();

}*/

void MainWindow::on_portStatusButton_clicked()
{
    QSerialPortInfo info(a.getarduino_port_name());

    QString portInfo = "arduino_uno_vendor: " + info.manufacturer() + "\n arduino_uno_producy: " + info.description();

    QMessageBox::information(this, "PORT Information",portInfo);

}

void MainWindow::on_disconnectButton_clicked()
{
    a.getserial()->clear();
    a.getserial()->close();
    if (!a.getserial()->isOpen()) QMessageBox::information(this, "Port is closed", "Connected device is closed successfully");
    ui->connectButton->setEnabled(true);
    ui->disconnectButton->setEnabled(false);
}

void MainWindow::on_connectButton_clicked()
{
    a.getserial()->setPortName(a.getarduino_port_name());


    if (a.getserial()->open(QIODevice::ReadWrite)){
          a.getserial()->setBaudRate(QSerialPort::Baud9600);
          a.getserial()->setDataBits(QSerialPort::Data8);
          a.getserial()->setParity(QSerialPort::NoParity);
          a.getserial()->setStopBits(QSerialPort::OneStop);
            // Skipping hw/sw control
          a.getserial()->setFlowControl(QSerialPort::NoFlowControl);
            QSerialPortInfo info(a.getarduino_port_name());
            QMessageBox::information(this, "Connection successful", "Successfully connected to : " + info.description());
    } else {
        QMessageBox::warning(this, "Connection Failed", "Retry");
    }

    ui->connectButton->setEnabled(false);
    ui->disconnectButton->setEnabled(true);


}

void MainWindow::on_envoyertexte_clicked()
{
    //If no arduino is detected it shows an warning
    if (!a.getserial()->isOpen()) QMessageBox::information(this, "No Arduino Detected", "Please connect an Arduino and click connect from Connection Manager");

    else {
        QByteArray text = ui->messageTextEdit->toPlainText().toLatin1();
        a.getserial()->write(text);
         }

}

void MainWindow::on_supprimertexte_clicked()
{
     ui->messageTextEdit->clear();
}

void MainWindow::on_clearLCDButton_clicked()
{    if (a.getserial()->isOpen()) a.getserial()->write("#");
    else QMessageBox::information(this, "No Arduino Detected", "Connect an Arduino and Click connect button on Connection Manager");
}



void MainWindow::on_fontsizeSpinBox_valueChanged(int arg1)
{
      ui->messageTextEdit->setFontPointSize(arg1);
}

void MainWindow::readArduino(){

    if (a.getserial()->canReadLine())
        data = a.getserial()->readLine();
        //data = data.remove(QRegExp("[\\n\\t\\r]"));
    if (data.contains("X")){
        qDebug() << data << "\n";
        ui->messageTextEdit->setText(data);
    }

}




