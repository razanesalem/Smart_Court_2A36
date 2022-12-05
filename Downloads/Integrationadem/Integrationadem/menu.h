#ifndef MENU_H
#define MENU_H

#include <QDialog>

#include <QDialog>
#include "mainwindow_acuucse.h"
namespace Ui
{
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:

    void on_menu_customers_clicked();

    void on_menu_sponsor_clicked();

    void on_menu_missions_clicked();

    void on_menu_transport_clicked();

    void on_pushButton_accuser_clicked();

    void on_menu_missions_2_clicked();

public:
    Ui::menu *ui;
private:
    MainWindow wiem;
};

#endif // MENU_H
