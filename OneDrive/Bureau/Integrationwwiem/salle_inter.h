#ifndef SALLE_INTER_H
#define SALLE_INTER_H

#include <QDialog>
#include"salle.h"

namespace Ui {
class salle_inter;
}

class salle_inter : public QDialog
{
    Q_OBJECT

public:
    explicit salle_inter(QWidget *parent = nullptr);
    ~salle_inter();
    private slots:
    void on_pushButton_clicked();




    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    bool search(int);

    void on_research_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_research_cursorPositionChanged(int arg1, int arg2);
    void input();

private:
    Ui::salle_inter *ui;
    salle s;

};

#endif // SALLE_INTER_H
