#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "affaire.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPrintPreviewDialog>
#include <QUrl>
#include "arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_radioButtontridate_clicked();


    void on_pushButtontri_clicked();

    void on_PDF_clicked();

    void on_pushButton_archiver_raz_clicked();

    void on_stat_raz_clicked();

    void on_desearchive_raz_clicked();

    void on_pushButton_4_clicked();


    void on_lineEdit_textChanged(const QString &arg1);

   //arduino
    /*void on_comportComboBox_currentIndexChanged(const QString &arg1);

    void on_baudRateComboBox_currentIndexChanged(const QString &arg1);

    void on_baudRateComboBox_currentIndexChanged(int index);*/


    void on_portStatusButton_clicked();

    void on_disconnectButton_clicked();

    void on_connectButton_clicked();

    void on_envoyertexte_clicked();

    void on_supprimertexte_clicked();

    void on_clearLCDButton_clicked();

    void on_fontsizeSpinBox_valueChanged(int arg1);

public slots:
    void readArduino();

private:
    Ui::MainWindow *ui;

    Affaire A;
    QByteArray data; // variable contenant les données reçues
    Arduino a; // objet temporaire
};

#endif // MAINWINDOW_H
