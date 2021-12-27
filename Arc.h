#ifndef ARC_H
#define ARC_H

#include "node.h"
class Arc
{
    Node firstNode, secondNode;
    int length;
    bool marcat;
public:
    Arc(Node n1, Node n2);
    Node getFirstPoint();
    Node getSecondPoint();
    void setLength(int length);
    int getLength();

    void setMarcat(bool color);
    bool getMarcat();

};
#endif // ARC_H
