
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;



void moveCamera(float simulationTime)
{
	float SpeedHorizontal = 130 * simulationTime;
	float SpeedVertical = 130 * simulationTime;
	float SpeedZoom = 2 * simulationTime;

	if(GetAsyncKeyState('W')) camera.rotateUpDown(SpeedVertical);
	if (GetAsyncKeyState('S')) camera.rotateUpDown(-SpeedVertical);
	if (GetAsyncKeyState('A')) camera.rotateLeftRight(SpeedHorizontal);
	if (GetAsyncKeyState('D')) camera.rotateLeftRight(-SpeedHorizontal);
	if (GetAsyncKeyState('E')) camera.zoomInOut(SpeedZoom);
	if (GetAsyncKeyState('Q')) camera.zoomInOut(-SpeedZoom);

};
double getSimulationTime() {
	float time;
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	time = (double)(end.QuadPart - previous.QuadPart) / frequency.QuadPart;
	return time;
};

void simulation()
{
	// ����������� ������� ���������
	double simulationTime = getSimulationTime();
	// ������������ ������
	moveCamera(simulationTime);
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
};