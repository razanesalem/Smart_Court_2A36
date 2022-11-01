#ifndef AFFICH_H
#define AFFICH_H

#include <QDialog>

namespace Ui {
class affich;
}

class affich : public QDialog
{
    Q_OBJECT

public:
    explicit affich(QWidget *parent = nullptr);
    ~affich();

private:
    Ui::affich *ui;
};

#endif // AFFICH_H
