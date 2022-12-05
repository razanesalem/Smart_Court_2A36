#include "mainwindow_acuucse.h"
#include "accuse.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QTextEdit>
#include "connexion.h"
#include "mainwindow_acuucse.h"
#include <QPrinter>
#include <QDesktopServices>
#include <QSqlQueryModel>
#include <QDialog>
#include <QPainter>
#include <QMap>
#include <QVector>
#include <QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGridLayout>
#include<QPdfWriter>
#include <QtQml/qqmlextensionplugin.h>
#include <QLoggingCategory>
#include <QApplication>
#include <QTableWidget>
#include <QSound>

#include <QSortFilterProxyModel>
QT_BEGIN_NAMESPACE


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_speech(0)
{
    ui->setupUi(this);
   // ui->tableView_aff->setModel(a.afficher_accuse());
    //ui->comboBox_affaire->setModel(a.afficher_accuse01());
    son=new QSound("C:/Users/Zakraoui/Pictures/gestion_accuser/wave.wav");



    qDebug()<<"start";


  //  QPixmap pix("C:/Users/Zakraoui/Pictures/gestion_accuser/court backg.png");
//ui->label_2->setPixmap(pix);
 QPixmap pix1("C:/Users/Zakraoui/Downloads/balsem/gestion_accuser/lol.jpg");
     ui->label_logo->setPixmap(pix1);
      ui->label_logo_2->setPixmap(pix1);
      ui->label_logo_3->setPixmap(pix1);
         ui->label_logo_4->setPixmap(pix1);
          ui->label_logo_5->setPixmap(pix1);
          ui->label_logo_6->setPixmap(pix1);

          //     QPixmap pix2("C:/Users/Zakraoui/Pictures/gestion_accuser/court (3).png");
     /*
         QPixmap pix3("C:/Users/Zakraoui/Pictures/gestion_accuser/court (3).png");

             QPixmap pi4("C:/Users/Zakraoui/Pictures/gestion_accuser/court (3).png");
              */
ui->lineEdit_nom_aj->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
ui->lineEdit_pren_aj->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
//ui->lineEdit_aff_ajou->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));

//textparole
QLoggingCategory::setFilterRules(QStringLiteral("qt.speech.tts=true \n qt.speech.tts.*=true"));

// Populate engine selection list
ui->engine->addItem("Default", QString("default"));
foreach (QString engine, QTextToSpeech::availableEngines())
    ui->engine->addItem(engine, engine);
ui->engine->setCurrentIndex(0);
engineSelected(0);

connect(ui->speakButton, &QPushButton::clicked, this, &MainWindow::speak);
connect(ui->pitch, &QSlider::valueChanged, this, &MainWindow::setPitch);
connect(ui->rate, &QSlider::valueChanged, this, &MainWindow::setRate);
connect(ui->volume, &QSlider::valueChanged, this, &MainWindow::setVolume);
connect(ui->engine, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::engineSelected);

//arduino
int ret=A.connect_arduino(); // lancer la connexion à arduino
switch(ret){
case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
    break;
case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
   break;
case(-1):qDebug() << "arduino is not available";
}
QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
// permet de lancer
//le slot update_label suite à la reception du signal readyRead (reception des données).
}


MainWindow::~MainWindow()
{
    A.close_arduino();
    delete ui;

}


void MainWindow::on_pushButton_ajouter_clicked()
{

    accuse c;
    son->play();
 c.setID(ui->lineEdit_id_ajou->text());
    c.setnom(ui->lineEdit_nom_aj->text());
    c.setprenom(ui->lineEdit_pren_aj->text());
   c.setEtat(ui->comboBox_aj->currentText());

    c.setAffaire(ui->comboBox_affaire->currentText());

    c.ajouter_accuse(c);
    ui->lineEdit_id_ajou->setText("");
    ui->lineEdit_nom_aj->setText("");
    ui->lineEdit_pren_aj->setText("");
    ui->comboBox_affaire->setCurrentText("");
    ui->comboBox_aj->setCurrentText("");

    ui->comboBox_affaire->setModel(c.afficher_accuse01());
    ui->tableView_aff->setModel(c.afficher_accuse());





}



void MainWindow::on_pushButton_supp_clicked()
{
    accuse c;
    c.setID(ui->lineEdit_id_ajou_supp->text());
    c.supprimer_accuse(c);
ui->lineEdit_id_ajou_supp->setText("");
ui->tableView_aff->setModel(c.afficher_accuse());

bool test=c.supprimer_accuse(c);
if(test)
{
    //ui->tableView_aff->setModel(a.afficher_accuse());


    QMessageBox::information(nullptr,QObject::tr("ok"),
                       QObject::tr("suprission affecte\n"
                             "click cancel to exit."), QMessageBox::Cancel);

}
else
{
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                       QObject::tr("Supprission non affectuer.\n"
                                   "click cancel to exit."),QMessageBox::Cancel  );}
}


void MainWindow::on_pushButton_ajouter_2_clicked()
{
    accuse c;


    c.setID(ui->lineEdit_id_ajou_2->text());
    c.setnom(ui->lineEdit_nom_aj_2->text());
    c.setprenom(ui->lineEdit_pren_aj_2->text());
    c.setAffaire(ui->lineEdit_aff_ajou_2->text());
    c.setEtat(ui->comboBox_mod->currentText());

    c.modifier_accuse(c);
    ui->lineEdit_id_ajou_2->setText("");
    ui->lineEdit_nom_aj_2->setText("");
    ui->lineEdit_pren_aj_2->setText("");
    ui->lineEdit_aff_ajou_2->setText("");
    ui->comboBox_mod->setCurrentText("");

    ui->tableView_aff->setModel(c.afficher_accuse());



}

void MainWindow::on_pushButton_clicked()
{
    accuse c;
QString rech =ui->lineEdit_cher->text();
ui->tableView_aff->setModel(c.chercher_accuse(rech));
}

void MainWindow::on_pushButton_trier_clicked()
{
    accuse c;
    //affichage simple
    ui->tableView_aff->setModel(c.afficher_accuse());
    if(QString::number(ui->comboBox->currentIndex())=="0"){
     ui->tableView_aff->setModel(c.afficher_accuse_trie_prenom());
}
    else
        if(QString::number(ui->comboBox->currentIndex())=="1"){
         ui->tableView_aff->setModel(c.afficher_accuse_trie_nom());
    }
        else
            if(QString::number(ui->comboBox->currentIndex())=="2"){
             ui->tableView_aff->setModel(c.afficher_accuse_trie_ID());
        }

}


void MainWindow::on_pushButton_pdf_clicked()
{//accuse c;


        QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tableView_aff->model()->rowCount();
                    const int columnCount =ui->tableView_aff->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Accuser</h1>"
                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView_aff->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView_aff->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tableView_aff->isColumnHidden(column)) {
                                       QString data = ui->tableView_aff->model()->data(ui->tableView_aff->model()->index(row, column)).toString().simplified();
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
            printer.setOutputFileName("accusertable.pdf");
            document->print(&printer);
            QDesktopServices::openUrl(QUrl("accusertable.pdf"));


}
void MainWindow::speak()
{
    m_speech->say(ui->plainTextEdit->toPlainText());
}
void MainWindow::stop()
{
    m_speech->stop();
}

void MainWindow::setRate(int rate)
{
    m_speech->setRate(rate / 10.0);
}

void MainWindow::setPitch(int pitch)
{
    m_speech->setPitch(pitch / 10.0);
}

void MainWindow::setVolume(int volume)
{
    m_speech->setVolume(volume / 100.0);
}

void MainWindow::stateChanged(QTextToSpeech::State state)
{
    if (state == QTextToSpeech::Speaking) {
        ui->statusbar->showMessage("Speech started...");
    } else if (state == QTextToSpeech::Ready)
        ui->statusbar->showMessage("Speech stopped...", 2000);
    else if (state == QTextToSpeech::Paused)
        ui->statusbar->showMessage("Speech paused...");
    else
        ui->statusbar->showMessage("Speech error!");

    ui->pauseButton->setEnabled(state == QTextToSpeech::Speaking);
    ui->resumeButton->setEnabled(state == QTextToSpeech::Paused);
    ui->stopButton->setEnabled(state == QTextToSpeech::Speaking || state == QTextToSpeech::Paused);
}

void MainWindow::engineSelected(int index)
{
    QString engineName = ui->engine->itemData(index).toString();
    delete m_speech;
    if (engineName == "default")
        m_speech = new QTextToSpeech(this);
    else
        m_speech = new QTextToSpeech(engineName, this);
    disconnect(ui->language, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::languageSelected);
    ui->language->clear();
    // Populate the languages combobox before connecting its signal.
    QVector<QLocale> locales = m_speech->availableLocales();
    QLocale current = m_speech->locale();
    foreach (const QLocale &locale, locales) {
        QString name(QString("%1 (%2)")
                     .arg(QLocale::languageToString(locale.language()))
                     .arg(QLocale::countryToString(locale.country())));
        QVariant localeVariant(locale);
        ui->language->addItem(name, localeVariant);
        if (locale.name() == current.name())
            current = locale;
    }
    setRate(ui->rate->value());
    setPitch(ui->pitch->value());
    setVolume(ui->volume->value());
    connect(ui->stopButton, &QPushButton::clicked, m_speech, &QTextToSpeech::stop);
    connect(ui->pauseButton, &QPushButton::clicked, m_speech, &QTextToSpeech::pause);
    connect(ui->resumeButton, &QPushButton::clicked, m_speech, &QTextToSpeech::resume);

    connect(m_speech, &QTextToSpeech::stateChanged, this, &MainWindow::stateChanged);
    connect(m_speech, &QTextToSpeech::localeChanged, this, &MainWindow::localeChanged);

    connect(ui->language, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::languageSelected);
    localeChanged(current);
}

void MainWindow::languageSelected(int language)
{
    QLocale locale = ui->language->itemData(language).toLocale();
    m_speech->setLocale(locale);
}

void MainWindow::voiceSelected(int index)
{
    m_speech->setVoice(m_voices.at(index));
}

void MainWindow::localeChanged(const QLocale &locale)
{
    QVariant localeVariant(locale);
    ui->language->setCurrentIndex(ui->language->findData(localeVariant));

    disconnect(ui->voice, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::voiceSelected);
    ui->voice->clear();

    m_voices = m_speech->availableVoices();
    QVoice currentVoice = m_speech->voice();
    foreach (const QVoice &voice, m_voices) {
        ui->voice->addItem(QString("%1 - %2 - %3").arg(voice.name())
                          .arg(QVoice::genderName(voice.gender()))
                          .arg(QVoice::ageName(voice.age())));
        if (voice.name() == currentVoice.name())
            ui->voice->setCurrentIndex(ui->voice->count() - 1);
    }
    connect(ui->voice, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::voiceSelected);
}



void MainWindow::on_pushButton_2_clicked()
{
    s = new statisque();

  s->setWindowTitle("statistique ComboBox");
  s->choix_pie();
  s->show();
}

void MainWindow::update_label()
{
data=A.read_from_arduino();

 ui->lineEdit_alert->setText(ui->lineEdit_alert->text()+data);
}

void MainWindow::on_pushButton_alerte_clicked()
{

 QString at ;


 bool ch= a.chercher_accuse01(ui->lineEdit_alert->text());

 if(ch)
 {

     QMessageBox::information(nullptr, QObject::tr("sql query successful"),
                        QObject::tr("Accuser found.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
 }

 else{
     QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                        QObject::tr("Accuser not found.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
 }

}


















