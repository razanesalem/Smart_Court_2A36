#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "affaire.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintPreviewDialog>

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

private:
    Ui::MainWindow *ui;

    Affaire A;
};

#endif // MAINWINDOW_H
