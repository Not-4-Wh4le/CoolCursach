#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "animalscene.h"

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
    AnimalScene *scene;

private slots:
               /// void addFood();
    void updateMutationChanceLabel(int);
    void on_startButton_clicked();

public slots:
    void completeSlot();

signals:
    void startSignal(int, int, int, int);
};



#endif // MAINWINDOW_H
