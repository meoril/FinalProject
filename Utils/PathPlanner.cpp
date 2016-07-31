#include "PathPlanner.h"
#include <iostream>
#include <map>

using namespace std;


PathPlanner::PathPlanner() {
    
}

std::list<Node*> PathPlanner::AStarPath (Point startPoint, Point goalPoint, Map *map)
{
    std::list<Node*> openList;
    std::list<Node*> closedList;
    //std::map<Node*, Node*> nSourceNodes;
    
    
    
    Node *nStart 	= new Node(startPoint.getX(), startPoint.getY(), true, NULL);
    Node *nEnd 		= new Node(goalPoint.getX(), goalPoint.getY(), true, NULL);
    Node *nCurrnt 	= new Node(-1, -1, true, NULL);
    Node *nNext;
    
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
                    if ((!isPointInOpenedList) && (map->isPointOccupiedInGrid(new Point(adjacentX, adjacentY))))
                    {
                        nNext = new Node(adjacentX, adjacentY, nCurrnt, NULL);
                        nNext->computeScores(nEnd);
                        nNext->setParent(nCurrnt);
                        openList.push_back(nNext);
                    }
                }
            }
        }
    }
    
    std::list<Node*> lstPath;
    
    while (nCurrnt->hasParent() && !nCurrnt->isEqual(nStart)){
        lstPath.push_front(nCurrnt);
        nCurrnt = nCurrnt->getParent();
    }
    
    return lstPath;
}

PathPlanner::~PathPlanner() {
}
