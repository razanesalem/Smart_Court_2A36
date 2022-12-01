#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>
#include "accuse.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QChart>

#include <QtCharts/QChartView>

#include <QChartGlobal>


namespace Ui {
class statistique;
}

class statistique : public QChart
{
    Q_OBJECT

public:
    explicit statistique(QWidget *parent = nullptr);
    ~statistique();
     QChartView *chartView ;
    void choix_bar();
    void choix_pie();


private:
    Ui::statistique *ui;
    accuse V1;

};

#endif // STATISTIQUE_H
