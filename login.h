#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QString>
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pb_conn_clicked();

private:
QString log,mdps;
    Ui::login *ui;
}

#endif // LOGIN_H
