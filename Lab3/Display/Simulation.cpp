
#include "Simulation.h"


extern LARGE_INTEGER previous, frequency;


void moveCamera(float simulationTime)
{
	float SpeedHorizontal = 130000 * simulationTime / 1000;
	float SpeedVertical = 130000 * simulationTime / 1000;
	float SpeedZoom = 20000 * simulationTime / 1000;

	if(GetAsyncKeyState(0x57)) camera.rotateUpDown(SpeedVertical);
	if (GetAsyncKeyState(0x53)) camera.rotateUpDown(-SpeedVertical);
	if (GetAsyncKeyState(0x41)) camera.rotateLeftRight(SpeedHorizontal);
	if (GetAsyncKeyState(0x44)) camera.rotateLeftRight(-SpeedHorizontal);
	if (GetAsyncKeyState(0x45)) camera.zoomInOut(SpeedZoom);
	if (GetAsyncKeyState(0x51)) camera.zoomInOut(-SpeedZoom);

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