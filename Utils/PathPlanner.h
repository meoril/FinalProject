#include <iostream>
#include <vector>
#include <list>
#include "../Utils/BaseUtils.h"
#include "../Models/Node.h"
#include "../Models/Map.h"

class PathPlanner {
    
public:
    PathPlanner();
    std::list<Node*> AStarPath (Point startPoint, Point goalPoint, Map *map);
    void isInList(Node *p, std::list<Node>& a);
    
    virtual ~PathPlanner();
};
