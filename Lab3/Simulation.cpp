
#include "Simulation.h"
#include "Data.h"
#include <iostream>

extern LARGE_INTEGER previous, frequency;

void moveCamera()
{
	// ��� �������� ������ ������ �������� ������ ������������
	
	if(GetAsyncKeyState(0x57)) camera.rotateUpDown(0.2);
	if (GetAsyncKeyState(0x53)) camera.rotateUpDown(-0.2);
	if (GetAsyncKeyState(0x41)) camera.rotateLeftRight(0.2);
	if (GetAsyncKeyState(0x44)) camera.rotateLeftRight(-0.2);
	if (GetAsyncKeyState(0x45)) camera.zoomInOut(0.02);
	if (GetAsyncKeyState(0x51)) camera.zoomInOut(-0.02);

};
double getSimulationTime() {
	double time;
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - previous.QuadPart) / frequency.QuadPart;
	return time;
};
void simulation()
{
	// ����������� ������� ���������
	double simulationTime = getSimulationTime();
	//std::cout << simulationTime << "\n";
	// ������������ ������
	moveCamera();
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
};