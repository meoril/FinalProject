
#include "BaseUtils.h"


int BaseUtils::DegreesToIndex(int degrees)
{
	int index = degrees * BaseUtils::DEGREES_INDEX_RATIO;
	return BaseUtils::MIDDLE_INDEX + index;
}

int BaseUtils::IndexToDegrees(int index)
{
	int realIndex = index - BaseUtils::MIDDLE_INDEX;
	return realIndex / BaseUtils::DEGREES_INDEX_RATIO;
}

double BaseUtils::IndexToRadians(int index)
{
	int degrees = IndexToDegrees(index);
	return degrees * PI / 180;
}

int BaseUtils::RadiansToIndex(double radians)
{
	int degrees = radians * 180 / PI;
	return DegreesToIndex(degrees);
}

double BaseUtils::DegreeToRadian(double degree){
	 return ((degree) * (M_PI / 180.0));
}

double BaseUtils::RadianToDegree(double radian){
	 return ((radian) * (180.0 / M_PI));
}

double BaseUtils::MeterToPixel(double meter){
	 return (meter * 100 / 2.5);
}

double BaseUtils::PixelToMeter(double pixel){
	 return (pixel * 2.5 / 100);
}

double BaseUtils::DegreeBetweenPoints(double dFirstX, double dFirstY, double dSecondX, double dSecondY)
{
	double dDeltaX = dSecondX - dFirstX;
	double dDeltaY = dSecondY - dFirstY;
	double absDelta = std::abs(dDeltaY / dDeltaX);
	double a = RadianToDegree(atan(absDelta));
	double dDegBetween = 0;
	if 		((dDeltaX < 0) && (dDeltaY < 0)) { dDegBetween = 180 - a; }
	else if ((dDeltaX < 0) && (dDeltaY >= 0)) { dDegBetween = 180 + a; }
	else if ((dDeltaX >= 0) && (dDeltaY >= 0)) { dDegBetween = 360 - a; }
	else { dDegBetween = a; }

	return dDegBetween;
}

double BaseUtils::Distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
