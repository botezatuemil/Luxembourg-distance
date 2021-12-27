#include "Arc.h"

Arc::Arc(Node n1, Node n2)
{
    firstNode = n1;
    secondNode = n2;
}

Node Arc::getFirstPoint()
{
    return firstNode;
}
Node Arc::getSecondPoint()
{
    return secondNode;
}

void Arc::setLength(int length)
{
    this->length = length;
}

int Arc::getLength()
{
    return length;
}

void Arc::setMarcat(bool marcat)
{
    this->marcat = marcat;
}

bool Arc::getMarcat()
{
    return marcat;
}
