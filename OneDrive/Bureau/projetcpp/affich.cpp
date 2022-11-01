#include "affich.h"
#include "ui_affich.h"

affich::affich(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affich)
{
    ui->setupUi(this);
}

affich::~affich()
{
    delete ui;
}
