#ifndef MAINWINDOW_CITOYEN_H
#define MAINWINDOW_CITOYEN_H

#include <QDialog>
#include "citoyen.h"
#include <QMainWindow>
#include <QDragEnterEvent>
#include <QListWidgetItem>
#include <QMimeData>
#include <QSerialPort>
#include<arduino.h>

namespace Ui {
class mainwindow_citoyen;
}

class mainwindow_citoyen : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow_citoyen(QWidget *parent = nullptr);
    ~mainwindow_citoyen();
private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_2_activated(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_load_clicked();

    void on_listView_indexesMoved(const QModelIndexList &indexes);

    void on_comboBox_3_activated(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);


    void on_listWidget_2_indexesMoved(const QModelIndexList &indexes);

    void on_listWidget_2_itemEntered(QListWidgetItem *item);

  void on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

  void on_pushButton_9_clicked();

  void on_save_clicked();

  void on_dateTimeEdit_dateChanged(const QDate &date);

  void on_pushButton_10_clicked();

  void on_pushButton_11_clicked();

  void on_pushButton_12_clicked();

  void on_pushButton_13_clicked();

  void on_comboBox_5_currentIndexChanged(const QString &arg1);

  void on_on_stat_raz_clicked();

  void on_stat_raz_clicked();
  void on_comboBox_5_currentTextChanged(const QString &arg1);

   void updatet(QString);
   void input();


   void on_pushButton_2_clicked();





private:
    Ui::mainwindow_citoyen *ui;
    citoyen etmp;
    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_product_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    //arduino A;
    QByteArray data;

};

#endif // MAINWINDOW_CITOYEN_H






