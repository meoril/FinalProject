#include "PathPlanner.h"
#include <iostream>
#include <map>

using namespace std;


PathPlanner::PathPlanner() {
    // TODO Auto-generated constructor stub
    
}

std::list<Node*> PathPlanner::AStarPath (Point startPoint, Point goalPoint, Map *map)
{
    std::list<Node*> openList;
    std::list<Node*> closedList;
    std::map<Node*, Node*> nSourceNodes;
    
    
    
    Node *nStart 	= new Node(startPoint.getX(), startPoint.getY(), NULL);
    Node *nEnd 		= new Node(goalPoint.getX(), goalPoint.getY(), NULL);
    Node *nCurrnt 	= new Node(-1, -1, NULL);
    
    nStart->computeScores(nEnd);
    
    openList.push_back(nStart);
    
    while (!nCurrnt->isEqual(nEnd))
    {
        // Search for node with the smallest F score in the open list
        for (std::list<Node*>::iterator listIterator = openList.begin(); listIterator != openList.end() ;listIterator++)
        {
            if ((listIterator == openList.begin()) || (*listIterator)->getFScore() < nCurrnt->getFScore())
            {
                nCurrnt = *listIterator;
            }
        }
        
        // Stop if we reached the end
        if (nCurrnt->isEqual(nEnd))
        {
            break;
        }
        
        // Remove the current point from the open list
        openList.remove(nCurrnt);
        
        // Add the current point to the closed list
        closedList.push_back(nCurrnt);
        
        // Scan all the adjacent points of the current point
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                // If its the current point - then pass
                if (i == 0 && j == 0)
                    continue;
                
                // If we are in a corner - then pass (we don't move in diagonal)
                //if (i != 0 && j != 0)
                //	continue;
                
                // calculate x & adjacentY of adjacent point
                int adjacentX = nCurrnt->getX() + j;
                int adjacentY = nCurrnt->getY() + i;
                
                // Check if this point is in the closed list
                bool isPointInClosedList = false;
                for (std::list<Node*>::iterator listIterator = closedList.begin(); listIterator != closedList.end(); listIterator++)
                {
                    if ((*listIterator)->getX() == adjacentX && (*listIterator)->getY() == adjacentY)
                    {
                        isPointInClosedList = true;
                        break;
                    }
                }
                
                // If this point is in the closed list - continue
                if (!isPointInClosedList)
                {
                    // Check if this point is in the open list
                    bool isPointInOpenedList = false;
                    for (std::list<Node*>::iterator listIterator = openList.begin(); listIterator != openList.end(); listIterator++)
                    {
                        if ((*listIterator)->getX() == adjacentX && (*listIterator)->getY() == adjacentY)
                        {
                            isPointInOpenedList = true;
                            break;
                        }
                    }
                    
                    // Check if cell is free and not in open list for the robot
                    if ((!isPointInOpenedList) && (map->isPointOccupied(new Point(adjacentX, adjacentY))))
                    {
                        Node *thisPoint = new Node(adjacentX, adjacentY, nCurrnt);
                        thisPoint->computeScores(nEnd);
                        openList.push_back(thisPoint);
                        
                        nSourceNodes[thisPoint] = nCurrnt;
                    }
                }
            }
        }
    }
    
    std::list<Node*> lstPath;
    Node *pathCurrent = nCurrnt;
    lstPath.push_front(nCurrnt);
    
    int changeXPrev = pathCurrent->getX() - nSourceNodes[pathCurrent]->getY();
    int changeYPrev = pathCurrent->getY() - nSourceNodes[pathCurrent]->getY();
    int changeX;
    int changeY;
    
    // Add all nodes in path to list - Take only nodes with changing in X or Y coords
    // relatively to the previos ones
    while (!pathCurrent->isEqual(nStart))
    {
        changeX = pathCurrent->getX() - nSourceNodes[pathCurrent]->getX();
        changeY = pathCurrent->getY() - nSourceNodes[pathCurrent]->getY();
        
        // if there is a change in X or in Y, add it to the list
        if ((changeX != changeXPrev) || (changeY != changeYPrev) || (nSourceNodes[pathCurrent]->isEqual(nStart)))
        {
            // if the father of the current is the starting point...path the current and add the start
            if (nSourceNodes[pathCurrent]->isEqual(nStart))
            {
                lstPath.push_front(nStart);
            }
            else
            {
                lstPath.push_front(pathCurrent);
            }
        }
        
        changeXPrev = changeX;
        changeYPrev = changeY;
        
        pathCurrent = nSourceNodes[pathCurrent];
    }
    
    return lstPath;
}

std::list<Node*> PathPlanner::AStarClearListByPrev(std::list<Node*> lstAll)
{
    std::list<Node*> lstToRet;
    std::list<Node*>::iterator curr = lstAll.begin();
    Node* prev = (Node*)(*curr);
    lstToRet.push_front(prev);
    curr++;
    double dSum = 0;
    double dCurrOffset;
    double dPrevOffset = BaseUtils::DegreeBetweenPoints(prev->getX(), prev->getY(), (*curr)->getX(),(*curr)->getY());
    
    while (curr != lstAll.end())
    {
        dCurrOffset = BaseUtils::DegreeBetweenPoints(prev->getX(), prev->getY(), (*curr)->getX(),(*curr)->getY());
        dSum += dCurrOffset - dPrevOffset;
        dPrevOffset = dCurrOffset;
        
        if ((dSum < -0.2) || (0.2 < dSum))
        {
            lstToRet.push_front(prev);
            dSum = 0;
            dCurrOffset = 0;
            dPrevOffset = BaseUtils::DegreeBetweenPoints(prev->getX(), prev->getY(), (*curr)->getX(),(*curr)->getY());
        }
        
        prev = (Node*)(*curr);
        curr++;
    }
    
    return (lstToRet);
}

std::list<Node*> PathPlanner::AStarClearList(std::list<Node*> lstAll, Point goalPoint)
{
    std::list<Node*> lstToRet;
    std::list<Node*>::iterator curr = lstAll.begin();
    Node* toComp = (Node*)(*curr);
    Node* prev =  toComp;
    int nCount = 0;
    lstToRet.push_back(toComp);
    curr++;
    
    double dCurrDiff;
    double dAVGDiffSum = 0;
    
    while (!(((*curr)->getX() == goalPoint.getX()) && ((*curr)->getY() == goalPoint.getY())))
    {
        dCurrDiff = BaseUtils::DegreeBetweenPoints(toComp->getX(), toComp->getY(), (*curr)->getX(),(*curr)->getY());
        dAVGDiffSum += dCurrDiff;
        nCount++;
        
        if ((dCurrDiff + 2 < dAVGDiffSum / nCount) || (dAVGDiffSum / nCount < dCurrDiff - 2))
        {
            lstToRet.push_back(prev);
            toComp = *curr;
            nCount = 0;
            dAVGDiffSum = 0;
        }
        
        prev = *curr;
        curr++;
    }
    
    lstToRet.push_back(*curr);
    
    return (lstToRet);
}

PathPlanner::~PathPlanner() {
}
