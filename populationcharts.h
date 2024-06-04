#ifndef POPULATIONCHARTS_H
#define POPULATIONCHARTS_H

#include <QMainWindow>
#include <QtCharts>
#include "animalBase.h"

namespace Ui {
class PopulationCharts;
}

class PopulationCharts : public QMainWindow
{
    Q_OBJECT

public:
    explicit PopulationCharts(QWidget *parent = nullptr);
    ~PopulationCharts();

private:
    Ui::PopulationCharts *ui;

    QValueAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;
    AnimalBase* list;
    static inline int time;
    QList<QBarSet*> barSets;
    QChart *populationChart;
    QChart *speedChart;
    QChart *sizeChart;
    QChart *energyChart;
    QLineSeries *population;
    QBarSet *speedSet;
    QBarSet *sizeSet;
    QBarSet *energySet;
    void updateBarSet(QBarSet *set, const QMap<int, int>& data);

public slots:
    void updateCharts(int, const QMap<int, int>&,  const QMap<int, int>&,  const QMap<int, int>&);

};

#endif // POPULATIONCHARTS_H
