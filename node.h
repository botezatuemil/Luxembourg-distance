#ifndef NODE_H
#define NODE_H

#include <QPainter>
#include <vector>
class Node
{
    QPointF point;
    int number;

public:
    Node(){ number = -1; };
    Node(QPointF p){
        point = p;
    }
    QPointF getPoint() {
        return point;
    }
    int getNumber() {
        return number;
    }
    void setNumber(int number) {
        this->number = number;
    }
    void setPoint(QPointF p) {
        this->point = p;
    }  

};

#endif // NODE_H
