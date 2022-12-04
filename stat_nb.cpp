#include "stat_nb.h"
#include "ui_stat_nb.h"
QT_CHARTS_USE_NAMESPACE
stat_nb::stat_nb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_nb)
{
    ui->setupUi(this);
}

stat_nb::~stat_nb()
{
    delete ui;
}
void stat_nb::stats()
{

    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM AVOCAT");
    q1.exec();

    q2.prepare("SELECT * FROM AVOCAT WHERE NB_AFF_G_AV >=0 and NB_AFF_G_AV <=25");
    q2.exec();

    q3.prepare("SELECT * FROM AVOCAT WHERE NB_AFF_G_AV >=26 and NB_AFF_G_AV <=75");
    q3.exec();

    q4.prepare("SELECT * FROM AVOCAT WHERE NB_AFF_G_AV >=76 ");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("0-25",c1);
    series->append("26-75",c2);
    series->append("76-",c3);




    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(621,471);

    chartView->show();


}
