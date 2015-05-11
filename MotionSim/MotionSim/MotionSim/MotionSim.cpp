#include <iostream>
#include <math.h>
//#include <vector>
#include "MotionSim.h"
using namespace std;

float pi = 3.1415927;

 
int MotionSim::posCalc(float time){
	int count = 0;
	float ang_tmp = 0;
	while (count < (time / dt)){
		motCond p1;
		motCond *p = &p1;
		p_Insert = realTime.rbegin();
		if (count == 0){
			p->x = 0;
			p->y = 0;
			p->ang = 0;
			p->x_vlc = angVlc1*cos(p->ang) + angVlc2*cos(p->ang + pi*0.6666667) + angVlc3*cos(p->ang + pi*1.3333333);
			p->y_vlc = -angVlc1*sin(p->ang) - angVlc2*sin(p->ang + pi*0.6666667) - angVlc3*sin(p->ang + pi*1.3333333);
			realTime.push_back(p1);
		}
		else{
			p->x = (p_Insert)->x + (p_Insert)->x_vlc*dt;
			p->y = (p_Insert)->y + (p_Insert)->y_vlc*dt;
			ang_tmp = (p_Insert)->ang + (angVlc1 + angVlc2 + angVlc3)*dt;
			if (ang_tmp>360){
				p->ang = ang_tmp - 360;
			}
			else{
				p->ang = ang_tmp;
			}
			p->x_vlc = angVlc1*cos(p->ang) + angVlc2*cos(p->ang + pi*0.6666667) + angVlc3*cos(p->ang + pi*1.3333333);
			p->y_vlc = -angVlc1*sin(p->ang) - angVlc2*sin(p->ang + pi*0.6666667) - angVlc3*sin(p->ang + pi*1.3333333);
		
			realTime.push_back(p1);	
		}
		count++;
	}
	return 0;
}


void MotionSim::setSpeed(float v1, float v2, float v3){
	angVlc1 = v1;
	angVlc2 = v2;
	angVlc3 = v3;
}
