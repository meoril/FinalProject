
#define PI 3.1415926536

#include <cmath>


class BaseUtils {
public:
	BaseUtils();

	enum CELL_STATUS {FREE = 0, BLOCK = 1, UNKNOWN = 2};
	static const double gridMapFinalResolution = 4;
	static const float DEGREES_INDEX_RATIO = 666 / 270;
	static const float MIDDLE_INDEX = 666 / 2;

	static const float UNSAFE_DIST = 0.6;

	static int IndexToDegrees(int index);
	static int DegreesToIndex(int degrees);

	static double IndexToRadians(int index);
	static int RadiansToIndex(double radians);

	static double PixelToMeter(double inPixel);
	static double MeterToPixel(double inMeter);

	static double DegreeToRadian(double degree);
	static double RadianToDegree(double radian);
	static double DegreeBetweenPoints(double dFirstX, double dFirstY, double dSecondX, double dSecondY);

	// Particles
 	static const int PARTICLES_NUMBER = 150;
	static const double MIN_BELIEF_THRESHOLD = 0.2;
	static const double GOOD_BELIEF_THRESHOLD = 0.7;

	// Probability
	static const double PERFECT_PROB = 0.99;
	static const double HIGH_PROB = 0.9;
	static const double MEDIUM_PROB = 0.6;
	static const double LOW_PROB = 0.4;

	// Laser Proxy
	static const float FORWARD_LASER_PROXY_VALUE = 332;
	static const float RIGHT_LASER_PROXY_VALUE = 50;
	static const float LEFT_LASER_PROXY_VALUE = 614;

	// Behavior
	static const float DISTANCE_TOLERANCE = 10;
	static const float MAX_LASER_INDEX = 665;

	// Others
	static const double ANGULAR_RESULUTION = 0.36;
};


