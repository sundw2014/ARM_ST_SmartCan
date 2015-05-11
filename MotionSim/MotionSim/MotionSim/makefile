RUN.o:main.o MotionSim.o MotionSim.h
	g++ main.o MotionSim.o -o RUN.o
main.o:main.cpp MotionSim.h 
	g++ -c main.cpp -o main.o
MotionSim.o:MotionSim.cpp MotionSim.h
	g++ -c MotionSim.cpp -o MotionSim.o
