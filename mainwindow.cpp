#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(MAX_X+50,MAX_Y+150);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    int half_X = MAX_X/2;
    int half_Y = MAX_Y/2;
    scene->setSceneRect(-half_X,-half_Y, MAX_X, MAX_Y);

    timer = new QTimer(this);
    connect(timer, SIGNAL( timeout() ), this, SLOT(oneStep() ));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawAxes()
{
    int half_X = MAX_X/2;
    int half_Y = MAX_Y/2;

    scene->addLine(0,0,half_X,0);
    scene->addLine(0,0,0,half_Y);

    scene->addLine(0,0,-half_X,0);
    scene->addLine(0,0,0,-half_Y);
    scene->addRect(-half_X, -half_Y, MAX_X, MAX_Y,
                   QPen(Qt::DotLine));
}

QPoint MainWindow::drawOneLine(QPoint center, int iAngle, qreal pRadius, QPen pen)
{
    qreal x,y;
    qreal alpha;
    QPoint end;

    alpha = qDegreesToRadians(static_cast<qreal>(iAngle));
    x = pRadius * qCos(alpha) + center.x();
    y = -pRadius * qSin(alpha) + center.y();
    end.setX(static_cast<int>(x));
    end.setY(static_cast<int>(y));
    QLine line(center, end);

    scene->addLine(line, pen);

    return end;
}

QPoint MainWindow::drawLines(QPoint center, qreal pRadius, QColor color)
{
    QPoint end;
    QPen pen(color);

    if (iDirection == 1) {
        for(int iA = 0; iA < iAngle; iA++) {
            end = drawOneLine(center, iA, pRadius, pen);
        }
    } else {
        for(int iA = 360; iA > iAngle; iA--) {
            end = drawOneLine(center, iA, pRadius, pen);
        }
    }

    return end;
}

void MainWindow::oneStep()
{
    QPoint pointCentral(0, 0);
    scene->clear();
    drawAxes();

    QPoint newStart = drawLines(pointCentral, radius, Qt::magenta);
    drawLines(newStart, radius/2, Qt::cyan);
    iAngle += iDirection;
    if (iAngle > 360 && iDirection == 1)
        iAngle = 0;
    else if (iAngle < 0 && iDirection == -1)
        iAngle = 360;
}

void MainWindow::on_btnStartCCW_clicked()
{
    iDirection = 1;
    iAngle = 0;
    timer->start(10);
}

void MainWindow::on_btnStop_clicked()
{
    timer->stop();
}

void MainWindow::on_btnStartCW_clicked()
{
    iAngle = 360;
    iDirection = -1;
    timer->start(10);
}
