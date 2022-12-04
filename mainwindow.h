#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "avocat.h"
#include <QMainWindow>
#include "stat_nb.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: //animation des bouttons
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_pb_trier_clicked();

    void on_pb_chercher_clicked();

    void on_pb_pdf_clicked();

    void on_pb_stat_clicked();
    void scanne();

private:
    Ui::MainWindow *ui;
    QByteArray data;
    Avocat A;
    Arduino R;
    stat_nb *s;
    Avocat tempavocat;
};
#endif // MAINWINDOW_H
