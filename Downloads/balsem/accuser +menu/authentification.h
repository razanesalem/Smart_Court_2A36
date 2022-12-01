#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H



#include <QDialog>
#include "mainwindow.h"
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
    void on_pushButton_clicked();
    void showTime();
private:
    Ui::authentification *ui;
    menu m;
    MainWindow * home;

};


#endif // AUTHENTIFICATION_H
