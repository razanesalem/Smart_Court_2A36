#ifndef AVOCAT_INTER_H
#define AVOCAT_INTER_H

#include <QMainWindow>
#include "avocat.h"
#include "stat_nb.h"
#include "arduino.h"
#include <QCompleter>
#include <QDirModel>

namespace Ui {
class Avocat_inter;
}

class Avocat_inter : public QMainWindow
{
    Q_OBJECT

public:
    explicit Avocat_inter(QWidget *parent = nullptr);
    ~Avocat_inter();

private slots:
    void on_pb_modifier_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_stat_clicked();

    void on_pb_pdf_clicked();

    void on_pb_trier_clicked();

    void scanne();
    void CompleteID();

    void on_le_id_cher_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::Avocat_inter *ui;
    QByteArray data;
    Avocat A;
    Arduino R;
    stat_nb *s;
    Avocat tempavocat;
    QCompleter * StringCompliter;
    QCompleter * ModelCompliter;

};

#endif // AVOCAT_INTER_H
