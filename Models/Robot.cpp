#include "Robot.h"

Robot::Robot(string strIP, int nPort, Position pStartPosition, Point pGoal, Size sRobotSize, bool bMotors)
{
    /*_playerClient = new PlayerClient(ip, port);
     _positionProxy = new Position2dProxy(_playerClient);
     _laserProxy = new LaserProxy(_playerClient);
     _laser = new Laser(*_laserProxy, *this);*/
    // _map = new Map(MAP_ROWS, MAP_COLUMNS, MAP_RESOLUTION);
    
    this->ip = strIP;
    this->port = nPort;
    this->robotStartPosition = pStartPosition;
    this->robotGoal = pGoal;
    this->robotSize = sRobotSize;
    this->startYaw = BaseUtils::DegreeToRadian(this->robotStartPosition.getYaw());
    
    // Connect to the emulator
    this->_playerClient = new PlayerClient(ip,port);
    
    // Init poistion proxy
    this->_positionProxy = new Position2dProxy(_playerClient);
    
    // Init laser proxy
    this->_laserProxy = new LaserProxy(_playerClient);
    
    this->_positionProxy->SetMotorEnable(bMotors);
    
    // Fixing player client read bug
    for(int read=0; read<50; read++){
        this->_playerClient->Read();
    }
    
    // Init robot yaw and odometry
    this->_positionProxy->SetOdometry(0,0,startYaw);
}

Robot::~Robot()
{
    delete _positionProxy;
    delete _laserProxy;
    delete _playerClient;
}



/* void Robot::getObstacles(vector<Point>& obstacles) const
 {
	_laser->getObstacles(LASER_OBSTACLE_DISTANCE, obstacles);
 }
 
 bool Robot::canRotate() const
 {
	return _laser->canRotate();
 }
 
 bool Robot::canMoveForward() const
 {
	return _laser->canMoveForward();
 }
 */




void Robot::Read()
{
    _playerClient->Read();
}

void Robot::refresh()
{
    // Refresh Sensors buffers
    _playerClient->Read();
    
    // Handle new Obstacles
    // vector<Point> obstacles;
    // getObstacles(obstacles);
    
    // map.handleObstacles(*this, obstacles);
    // cout << map << endl;
}

void Robot::setSpeed(double speed, double angularSpeed)
{
    _positionProxy->SetSpeed(speed,angularSpeed);
}

float Robot::getLaserScan(int index){
    return _laserProxy->GetRange(index);
}

void Robot::setOdometry()
{
    _positionProxy->SetOdometry(0,0,startYaw);
}

void Robot::setOdometry(int x, int y, double yaw)
{
    int newX = BaseUtils::PixelToMeter(x - this->robotStartPosition.getX());
    int newY = BaseUtils::PixelToMeter(y - this->robotStartPosition.getY());
    
    
    double radianYaw = BaseUtils::DegreeToRadian(yaw);
    
    _positionProxy->SetOdometry(newX, newY,radianYaw);
}

double Robot::getX()
{
    return this->robotStartPosition.getX() + BaseUtils::MeterToPixel(_positionProxy->GetXPos());
}

double Robot::getY()
{
    return this->robotStartPosition.getY() - BaseUtils::MeterToPixel(_positionProxy->GetYPos());
}
double Robot::getMatrixX()
{
    return getX() / BaseUtils::gridMapFinalResolution;
}

double Robot::getMatrixY()
{
    return getY() / BaseUtils::gridMapFinalResolution;
}

double Robot::getYaw()
{
    double degree = BaseUtils::RadianToDegree(_positionProxy->GetYaw());
    if (degree < 0)
        degree = 360 + degree;
    
    return degree;
}

LaserProxy* Robot::getLaserProxy()
{
    return _laserProxy;
}
