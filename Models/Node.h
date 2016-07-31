#ifndef NODE_H_
#define NODE_H_
#include "Point.h"

#include <cstdlib>
#include <iostream>

class Node
{
public:
    
    Node();
    Node(int x, int y, bool w, Node* parent);
    
    Point* getPoint();
    Node* getParent();
    
    void setParent(Node *p);
    void computeScores(Node *end);
    
    int getX();
    int getY();
    int getGScore(Node *p);
    int getHScore(Node *p);
    int getGScore();
    int getHScore();
    int getFScore();
    
    float getXf();
    float getYf();
    
    bool hasParent();
    bool isEqual(Node *comparedNode);
    
    bool walkable;
    bool closed;
    bool opened;
    
    
    private :
    
    int x;
    int y;
    
    unsigned int f;
    unsigned int g;
    unsigned int h;
    
    Node *parent;
};
#endif
