#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#include <QDialog>
#include <QString>
namespace Ui {
class Authentification;
}

class Authentification : public QDialog
{
    Q_OBJECT

public:
    explicit Authentification(QWidget *parent = nullptr);

    ~Authentification();

private slots:
    void on_pb_conn_clicked();

private:
    Ui::Authentification *ui;

};

#endif // AUTHENTIFICATION_H
