#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
//#include <vector>
#include "MotionSim.h"
using namespace std;
int main(){
//	freopen("data.m", "w", stdout);
	MotionSim simTest(0.001);
	simTest.setSpeed(20, -15, -5);
	simTest.posCalc(100);
	simTest.p_Flag = simTest.realTime.begin();
	cout << "A=[" << endl;
	while (simTest.p_Flag!=simTest.realTime.end()){
		/*cout << "x=" << simTest.p_Flag->x << endl;
		cout << "y=" << simTest.p_Flag->y << endl;
		cout << "ang=" << simTest.p_Flag->ang << endl;
		cout << "x_speed=" << simTest.p_Flag->x_vlc << endl;
		cout << "y_speed=" << simTest.p_Flag->y_vlc << endl;*/
		cout <<simTest.p_Flag->x << endl;
		cout << endl;
		++simTest.p_Flag;
	}
	cout << "]" << endl;
	simTest.p_Flag = simTest.realTime.begin();
	cout << "B=[" << endl;
	while (simTest.p_Flag != simTest.realTime.end()){
		/*cout << "x=" << simTest.p_Flag->x << endl;
		cout << "y=" << simTest.p_Flag->y << endl;
		cout << "ang=" << simTest.p_Flag->ang << endl;
		cout << "x_speed=" << simTest.p_Flag->x_vlc << endl;
		cout << "y_speed=" << simTest.p_Flag->y_vlc << endl;*/
			cout << simTest.p_Flag->y << endl;
		cout << endl;
		++simTest.p_Flag;
	}
	cout << "]" << endl;
	cout << "plot(A,B);axis([-10,10,-10,10]);" << endl;
	return 0;
}
