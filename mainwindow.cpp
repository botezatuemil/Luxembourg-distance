#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include "graf.h"
#include <QMouseEvent>
#include <QPainter>
#include <iostream>
#include "QDebug"
#include"Arc.h"
#include "QDesktopWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawNode = false;
    drawArc = false;
    ui->setupUi(this);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    drawNode=false;
    drawArc=false;

    if(e->button()==Qt::RightButton)
    {
        int index=0;
        Node n(e->pos());
        QPointF point1=n.getPoint();

        if(g.verifyDistance(point1)==true)  {
            if(g.GetNoduri().size()>0)
            {
                index=g.GetLastNode().getNumber();
                n.setNumber(index++);
            }

            else n.setNumber(1);
            g.AddNod(n);
            drawNode=true;
            update();
            firstNode=Node();
        }
    }
    else
    {
        QPointF p = e->localPos();
        std::vector<Node> noduri = g.GetNoduri();
        Node foundNode;

        int threshold = 5;

        if (radacina) {
            threshold = 60;
        }

        for (auto& n : noduri)
        {
            if (fabs(n.getPoint().x() - p.x()) < threshold && fabs(n.getPoint().y() - p.y()) < threshold)
            {
                foundNode = n;
                break;
            }
        }
        if (foundNode.getNumber() == -1)
            return;
        if (firstNode.getNumber() == -1)
        {
            firstNode = foundNode;
        }
        else
        {
            secondNode = foundNode;
            if (g.verificareMultiGraf(firstNode, foundNode)) {
                if (radacina) {
                    g.AddArc(Arc(firstNode, secondNode));
                }
                else {
                    g.Dijkstra(firstNode, secondNode);
                }

                firstNode = Node();
                secondNode = Node();
                drawArc = true;
                update();
            }
            else {
                firstNode.setNumber(-1);
            }

        }
    }

}

void MainWindow::pressMouseButton(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {

        QPointF p = e->localPos();
        std::vector<Node> noduri = g.GetNoduri();

        for (auto& n : noduri)
        {
            if (fabs(n.getPoint().x() - p.x()) < 20 && fabs(n.getPoint().y() - p.y()) < 20)
            {
                myPressedNode = &n;
            }
        }
    }
}

void MainWindow::moveNode(QMouseEvent *e)
{
    QPointF p = e->localPos();

    if (myPressedNode) {
        myPressedNode->setPoint(p);
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    if (luxemburg) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        std::vector<Arc> arce = g.GetArce();

        for(auto& arc: arce)
        {
            if (arc.getMarcat()) {
                p.setPen(QPen(Qt::red, 2));

            }
            else {
                p.setPen(QPen(Qt::black));
            }

            p.drawLine(arc.getFirstPoint().getPoint(), arc.getSecondPoint().getPoint());

        }
        update();
    }
    else {
        QPainter p(this);
        std::vector<Node> noduri = g.GetNoduri();

        for(auto& nod: noduri)
        {
            p.setBrush(Qt::red);
            QRect r(nod.getPoint().x()-10,nod.getPoint().y()-10, 40,40);
            p.drawEllipse(r);
            p.drawText(QPoint(nod.getPoint().x() + 5, nod.getPoint().y() + 15), QString::number(nod.getNumber()));
        }


        std::vector<Arc> arce = g.GetArce();

        for(auto& arc: arce)
        {

            QLineF lineUp;
            QLineF lineDown;
            QLineF lineBetween;
            QPointF firstPoint = arc.getFirstPoint().getPoint();
            QPointF secondPoint = arc.getSecondPoint().getPoint();

            if (firstPoint != secondPoint) {

                lineUp.setP1(secondPoint);
                lineDown.setP1(secondPoint);
                lineBetween.setLine(firstPoint.x(), firstPoint.y(), secondPoint.x(), secondPoint.y());

                lineUp.setAngle(lineBetween.angle() + 150);
                lineDown.setAngle(lineBetween.angle() - 150);
                lineUp.setLength(15);
                lineDown.setLength(15);

                p.drawLine(lineBetween);
                p.drawLine(lineUp);
                p.drawLine(lineDown);
            }

        }

        if (drawNode)
        {
            Node n = g.GetLastNode();
            p.setBrush(Qt::green);
            QRect r(n.getPoint().x()-10,n.getPoint().y()-10, 40,40);
            p.drawEllipse(r);
            p.drawText(QPoint(n.getPoint().x() + 5, n.getPoint().y() + 15), QString::number(n.getNumber()));
        }
        else if (drawArc)
        {
            p.setPen(QPen(Qt::red, 2));
            p.drawLine(QLineF(arce[arce.size()-1].getFirstPoint().getPoint(), arce[arce.size()-1].getSecondPoint().getPoint()));

        }
        update();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radacina_clicked()
{


    g.gasireRadacina();
}


void MainWindow::on_luxemburg_clicked()
{
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height() -200;
    int width = rec.width() - 400;


    luxemburg = true;
    radacina = false;

    g.gasireMinMax();
    g.adaugareNoduri(height, width);
}


void MainWindow::on_desenare_clicked()
{
    radacina = true;
    luxemburg = false;
}

