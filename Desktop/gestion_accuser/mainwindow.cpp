#include "Accuser.h"
#include "mainwindow.h"
#include"ui_mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDialog>

#include <QtSql/QSqlDatabase>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Ajouter_button_clicked()
{
Accuser a;
a.ajouter(ui);
}




void MainWindow::on_pushButton_7_clicked()
{
    Accuser c;
    c.Modifier(ui);
}


void MainWindow::on_pushButton_aff_clicked()
{
    Accuser c;
    c.AfficherTable(ui);
}

void MainWindow::on_pushButton_6_clicked()
{
    Accuser c;
    c.supprimer(ui);
}
