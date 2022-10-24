#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Accuser.h"
#include <QMainWindow>

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
    void on_Ajouter_button_clicked( );

    void on_pushButton_7_clicked( );

    void on_pushButton_5_clicked( );

    void on_pushButton_aff_clicked( );

    void on_pushButton_6_clicked( );

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
