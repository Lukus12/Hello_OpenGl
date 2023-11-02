
#include "Simulation.h"


extern LARGE_INTEGER previous, frequency;


void moveCamera(float simulationTime)
{
	float SpeedHorizontal = 1300 * simulationTime;
	float SpeedVertical = 1300 * simulationTime;
	float SpeedZoom = 200 * simulationTime;

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
	// определение времени симуляции
	double simulationTime = getSimulationTime();
	//std::cout << simulationTime << "\n";
	// передвижение камеры
	moveCamera(simulationTime);

	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};