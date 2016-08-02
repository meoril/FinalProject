#include "Node.h"
#include <iostream>
#include <cstdlib>


using namespace std;
Node::Node()
{
	parent = NULL;
    closed = false;
    opened = false;

    x = y = f = g = h = 0;
}

Node::Node(int x, int y, bool w, Node *parent)
{
	Node();
	this->parent = parent;
    this->walkable = w;
    this->x = x;
    this->y = y;
}

Point* Node::getPoint()
{
    return new Point(x, y);
}

Node* Node::getParent()
{
    return parent;
}

void Node::setParent(Node *p)
{
    parent = p;
}

int Node::getX()
{
    return x;
}

int Node::getY()
{
    return y;
}

float Node::getXf()
{
    return (float)x;
}

float Node::getYf()
{
    return (float)y;
}

int Node::getGScore(Node *p)
{
	if (p->getX() != this->getX() && p->getY() != this->getY()){
		return p->getGScore() + 14;
	}

    return p->getGScore() + 10;
}

int Node::getHScore(Node *p)
{
    return (abs(p->x - x) + abs(p->y - y)) * 10;
}

int Node::getGScore()
{
    return g;
}

int Node::getHScore()
{
    return h;
}

int Node::getFScore()
{
    return f;
}

void Node::computeScores(Node *end)
{
	if (this->parent != NULL){
		g = this->getGScore(this->parent);
	}
	else{
		g = 0;
	}

    h = getHScore(end);
    f = g + h;
}

bool Node::hasParent()
{
    return parent != NULL;
}

bool Node::isEqual(Node *comparedNode)
{
	return ((this->getX() == comparedNode->getX()) && (this->getY() == comparedNode->getY()));
}
