#ifndef ANIMALSCENE_H
#define ANIMALSCENE_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsScene>
#include <QTime>
#include "food.h"
#include "animalBase.h"
#include "populationcharts.h"
#include "customanimal.h"


namespace Ui {
class AnimalScene;
}

class AnimalScene : public QWidget
{
    Q_OBJECT

public:
    explicit AnimalScene(QWidget *parent = nullptr);
    ~AnimalScene();
    QGraphicsScene *scene;
    //StartDialog *dialog;
    QTimer *timer;
    QTimer *lifeTimer;
    QTimer *foodTimer;
    QTime lastFood;
    QMap<int, int> speed;
    QMap<int, int> protection;
    QMap<int, int> size;

    QList<Food*> foodList;
    QList<AnimalBase*> animalList;
    void predatorBehavior(AnimalBase*);
    void herbivoreBehavior(AnimalBase*);
    int fieldSize;
    int bacteriaCount;
    int foodCount;
    int mutationChance;


    //void startScreen();

private slots:
    // void on_startBtn_clicked();
    //void on_stopBtn_clicked();
    //void slotTimer();
    void changeSpeed();
    void behavior();
    void createNewFood();
    void updateCharts();

    void on_resumeButton_clicked();

    void on_pauseButton_clicked();

    void on_completeButton_clicked();

    void on_switchButton_clicked();

    void on_customAnimalButton_clicked();

    void on_settingAnimalButton_clicked();

public slots:
    void start(int, int, int, int);

private:
    Ui::AnimalScene *ui;
    int programSpeed;
    int lifeSpeed;
    PopulationCharts *charts;
    CustomAnimal *custom;

signals:
    void completeSignal();
    void updateChartsSignal(int, const QMap<int, int>&, const QMap<int, int>&, const QMap<int, int>&);
};

#endif // ANIMALSCENE_H
