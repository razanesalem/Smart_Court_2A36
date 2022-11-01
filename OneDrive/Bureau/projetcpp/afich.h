  #ifndef AFICH_H
#define AFICH_H

#include <QDialog>

namespace Ui {
class afich;
}

class afich : public QDialog
{
    Q_OBJECT

public:
    explicit afich(QWidget *parent = nullptr);
    ~afich();

private:
    Ui::afich *ui;
};

#endif // AFICH_H
