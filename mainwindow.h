#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>

#include <QGraphicsItemGroup>

#include <QTimer>
#include <QtMath>


#define MAX_X 700
#define MAX_Y 450

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:    
    void oneStep();
    void on_btnStartCCW_clicked();

    void on_btnStop_clicked();

    void on_btnStartCW_clicked();

private:

    QPoint drawOneLine(QPoint center, int iAngle, qreal pRadius, QPen pen);
    QPoint drawLines(QPoint center, qreal pRadius, QColor color);
    void drawAxes();

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer;

    qreal radius = 100.0;
    int iAngle;
    int iDirection;

};

#endif // MAINWINDOW_H
