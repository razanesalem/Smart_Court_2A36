#ifndef GESTION_DES_EM_H
#define GESTION_DES_EM_H
#include "employer.h"
#include <QMainWindow>
#include "smtp.h"
#include "arduino.h"



namespace Ui {
class gestion_des_em;
}

class gestion_des_em : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_des_em(QWidget *parent = nullptr);
    ~gestion_des_em();

private slots:


    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_pb_pdf_clicked();
    void on_comboBox_tri_currentIndexChanged(const QString &arg1);
    void on_lineEdit_cherche_cin_textChanged(const QString &arg1);
    void on_pushButton_imprimer_clicked();
    void on_pb_modif_currentIndexChanged(int index);
    void on_stat_clicked();
    void on_pushButton_envoyer_clicked();
    void update_label();


private:
    Ui::gestion_des_em *ui;
    Employer E;
    QStringList  files;
    QByteArray data;
    Arduino A;
    QString c="";

};

#endif // GESTION_DES_EM_H
