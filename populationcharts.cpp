#include "populationcharts.h"
#include "ui_populationcharts.h"

PopulationCharts::PopulationCharts(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PopulationCharts)
{
    ui->setupUi(this);
    populationChart = new QChart();
    population = new QLineSeries(this);
    populationChart->addSeries(population);
    axisX = new QValueAxis(this);
    axisY = new QValueAxis(this);
    // В вашем классе или в функции инициализации:
    axisX->setTitleText("Время");
    axisX->setTickCount(10);
    axisX->setLabelFormat("%d");
    axisX->setRange(0, 100);  // Установите начальный диапазон для оси X

    axisY->setTitleText("Численность популяции");
    axisY->setRange(0, 100);  // Установите начальный диапазон для оси Y

    populationChart->addAxis(axisX, Qt::AlignBottom);
    populationChart->addAxis(axisY, Qt::AlignLeft);

    population->attachAxis(axisX);
    population->attachAxis(axisY);

    chartView = new QChartView(populationChart);
    chartView->setRenderHint(QPainter::Antialiasing);



    speedSet = new QBarSet("Численность по скоростям", this);
    sizeSet = new QBarSet("Численность по размерам", this);
    energySet = new QBarSet("Численность по энергии", this);

    *speedSet << 75;
    *sizeSet << 75;
    *energySet << 75;


    QBarSeries *speedSeries = new QBarSeries(this);
    speedSeries->append(speedSet);

    QBarSeries *sizeSeries = new QBarSeries(this);
    sizeSeries->append(sizeSet);

    QBarSeries *energySeries = new QBarSeries(this);
    energySeries->append(energySet);

    speedChart = new QChart();
    speedChart->addSeries(speedSeries);
    //speedChart->setTitle("Численность по скоростям");
    speedChart->setAnimationOptions(QChart::SeriesAnimations);
    speedChart->setAnimationOptions(QChart::NoAnimation);

    sizeChart = new QChart();
    sizeChart->addSeries(sizeSeries);
    //sizeChart->setTitle("Численность по размерам");
    sizeChart->setAnimationOptions(QChart::SeriesAnimations);
    sizeChart->setAnimationOptions(QChart::NoAnimation);

    energyChart = new QChart();
    energyChart->addSeries(energySeries);
    //energyChart->setTitle("Численность по энергии");
    energyChart->setAnimationOptions(QChart::SeriesAnimations);
    energyChart->setAnimationOptions(QChart::NoAnimation);

    QStringList categories;
    for (int i = 1; i < 21; ++i){
        categories << QString:: number(i);
    }


    // Настройка осей для каждого графика
    QBarCategoryAxis *speedAxisX = new QBarCategoryAxis(this);
    speedAxisX->append(categories);
    QValueAxis *speedAxisY = new QValueAxis(this);
    speedAxisY->setTitleText("Численность");

    QBarCategoryAxis *sizeAxisX = new QBarCategoryAxis(this);
    sizeAxisX->append(categories);
    QValueAxis *sizeAxisY = new QValueAxis(this);
    sizeAxisY->setTitleText("Численность");

    QBarCategoryAxis *energyAxisX = new QBarCategoryAxis(this);
    energyAxisX->append(categories);
    QValueAxis *energyAxisY = new QValueAxis(this);
    energyAxisY->setTitleText("Численность");

    // Привязка осей к диаграммам
    speedChart->addAxis(speedAxisX, Qt::AlignBottom);
    speedChart->addAxis(speedAxisY, Qt::AlignLeft);
    speedSeries->attachAxis(speedAxisX);
    speedSeries->attachAxis(speedAxisY);

    sizeChart->addAxis(sizeAxisX, Qt::AlignBottom);
    sizeChart->addAxis(sizeAxisY, Qt::AlignLeft);
    sizeSeries->attachAxis(sizeAxisX);
    sizeSeries->attachAxis(sizeAxisY);

    energyChart->addAxis(energyAxisX, Qt::AlignBottom);
    energyChart->addAxis(energyAxisY, Qt::AlignLeft);
    energySeries->attachAxis(energyAxisX);
    energySeries->attachAxis(energyAxisY);

    ui->gridLayout->addWidget(chartView, 0, 0);
    ui->gridLayout->addWidget(new QChartView(speedChart, this), 0, 1);
    ui->gridLayout->addWidget(new QChartView(sizeChart, this), 1, 0);
    ui->gridLayout->addWidget(new QChartView(energyChart, this), 1, 1);


    time = 0;

}

PopulationCharts::~PopulationCharts()
{
    delete ui;
}




void PopulationCharts::updateCharts(int a, const QMap<int, int>& b, const QMap<int, int>& c, const QMap<int, int>& d)
{
    *population << QPointF(time, a);
    axisX->setRange(qMax(0, time - 10), time);
    axisY->setRange(0, qMax(a, int(axisY->max())));
    // for(int i = 0; i <= 10; ++i){
    //     qDebug()<< b[i];
    // }
    ++time;
    updateBarSet(speedSet, b);
    updateBarSet(energySet, c);
    updateBarSet(sizeSet, d);


}


void PopulationCharts::updateBarSet(QBarSet *set, const QMap<int, int> &data)
{
    set->remove(0, set->count()); // Очистка текущих данных
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        *set << it.value(); // Добавление новых данных
    }
}


