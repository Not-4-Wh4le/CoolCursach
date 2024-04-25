#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QTime>
#include "food.h"
#include "herbivore.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QTime lastFood;
    void createNewFood();
    void behavior();
    QList<Food*> foodList;
    QList<Herbivore*> animalList;

private slots:
    void on_startBtn_clicked();
    void slotTimer();

};



#endif // MAINWINDOW_H
