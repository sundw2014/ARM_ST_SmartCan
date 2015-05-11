#ifndef _MOTIONSIM_H_

#define _MOTIONSIM_H_

#include <vector>
//#include "MotionSim.h"
using namespace std;

struct motCond{
	float x;
	float y;
	float ang;
	float x_vlc;
	float y_vlc;
};


class MotionSim{
public:
	MotionSim(float t) :dt(t){}
	const float dt;
	float angVlc1;
	float angVlc2;
	float angVlc3;
	vector<motCond>::iterator p_Flag;
	vector<motCond>::reverse_iterator p_Insert;
	vector<motCond> realTime;//static
	int posCalc(float time);
	void setSpeed(float v1, float v2, float v3);
};
#endif