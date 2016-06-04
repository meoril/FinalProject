#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "../Utils/BaseUtils.h"
#include "../Models/Point.h"
#include "../Models/Position.h"
#include "../Models/Size.h"
#include <vector>

using namespace std;
using namespace PlayerCc;

class Robot {
    
    PlayerClient* _playerClient;
    Position2dProxy* _positionProxy;
    LaserProxy* _laserProxy;
    int X;
    int Y;
    int Yaw;
    double startYaw;
    string ip;
    int port;
    
public:
    Robot(string strIP, int nPort, Position pStartPosition, Point pGoal, Size sRobotSize, bool bMotors);
    double getX() const;
    double getY() const;
    double getYaw() const;
    Position robotStartPosition;
    Point robotGoal;
    Size robotSize;
    
    // void getObstacles(vector<Point>& obstacles) const;
    
    bool canRotate() const;
    bool canMoveForward() const;
    
    void refresh();
    void setSpeed(double speed, double angularSpeed);
    void Read();
    float getLaserScan(int index);
    void setOdometry();
    void setOdometry(int x, int y, double yaw);
    double getX();
    double getY();
    double getMatrixX();
    double getMatrixY();
    double getYaw();
    LaserProxy* getLaserProxy();
    
    virtual ~Robot();
};
#endif
