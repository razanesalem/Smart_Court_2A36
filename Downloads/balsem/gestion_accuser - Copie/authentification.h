#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QDialog>
#include "mainwindow_acuucse.h"
#include "menu.h"

namespace Ui {
class authentification;
}

class authentification : public QDialog
{
    Q_OBJECT

public:
    explicit authentification(QWidget *parent = nullptr);
    ~authentification();

private slots:
    void showTime();
    void on_pushButton_2_clicked();

private:
    Ui::authentification *ui;
    menu m;
    MainWindow *home;

};


#endif // AUTHENTIFICATION_H
