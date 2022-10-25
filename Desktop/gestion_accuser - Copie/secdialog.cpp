#include "secdialog.h"
#include "ui_secdialog.h"
#include <QMessageBox>

#include "ui_mainwindow.h"
MainWindow *uimain;
secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::on_login_clicked()
{
  QString username=ui->lineEdit_pass->text();
 QString password=ui->lineEdit_user->text();
 if(username=="test" && password=="test")
 { QMessageBox::information(this,"login","username and password correct");

 }
 else
 {QMessageBox::critical(this,"login","username and password uncorrect");}
}
