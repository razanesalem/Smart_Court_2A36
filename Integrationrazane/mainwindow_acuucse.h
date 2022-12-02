#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QMainWindow>
#include "accuse.h"
#include <QSqlQuery>
#include <QTextToSpeech>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmainwindow.h>
#include "accuse_stat.h"
#include "ui_mainwindow_acuucse.h"
#include <QSqlQueryModel>
#include <QSound>

#include <QSortFilterProxyModel>

#include <QTextToSpeech>

#include "Arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();


    void on_pushButton_supp_clicked();



    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_trier_clicked();


    void on_pushButton_pdf_clicked();

    void speak();
    void stop();

    void setRate(int);
    void setPitch(int);
    void setVolume(int volume);

    void stateChanged(QTextToSpeech::State state);
    void engineSelected(int index);
    void languageSelected(int language);
    void voiceSelected(int index);

    void localeChanged(const QLocale &locale);


    void on_pushButton_2_clicked();
    void on_pushButton_alerte_clicked();

void update_label();




private:
    Ui::MainWindow *ui;
    statisque *s;
    accuse a;
    QSound *son;
  QSortFilterProxyModel *proxy;

    QTextToSpeech *m_speech;
    QVector<QVoice> m_voices;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
