#include "afich.h"
#include "ui_afich.h"

afich::afich(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::afich)
{
    ui->setupUi(this);
}

afich::~afich()
{
    delete ui;
}
