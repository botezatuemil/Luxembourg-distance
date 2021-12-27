#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graf.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void pressMouseButton(QMouseEvent *e);
    virtual void moveNode(QMouseEvent *e);
;   virtual void paintEvent(QPaintEvent *event);
    ~MainWindow();


private slots:

    void on_radacina_clicked();

    void on_luxemburg_clicked();

    void on_desenare_clicked();

private:
    Ui::MainWindow *ui;
    Graf g;
    Node firstNode, secondNode;
    bool drawNode, drawArc;
    Node *myPressedNode;
    bool luxemburg = false, radacina = false;

};


#endif // MAINWINDOW_H
