#ifndef STATISQUE_H
#define STATISQUE_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class statisque;
}



class statisque : public QDialog
{
    Q_OBJECT

public:
    explicit statisque(QWidget *parent = nullptr);
    ~statisque();
    QChartView *chartView ;
    void choix_bar();
    void choix_pie();

private:
    Ui::statisque *ui;
};

#endif // STATISQUE_H
