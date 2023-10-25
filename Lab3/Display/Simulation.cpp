
#include "Simulation.h"


extern LARGE_INTEGER previous, frequency;


void moveCamera(float simulationTime) {
	// Нейминг вышел из чата
	// l - local
	float lSpeedHorizontal = 130 * simulationTime;
	float lSpeedVertical = 130 * simulationTime;
	float lSpeedZoom = 20 * simulationTime;

	// Взгляд падает на кондишины, а не их ветвления
	// Мне тоже нравиться абстракция,
	// но лучше указать, что значит 0x57 и т.п.
	if (GetAsyncKeyState(0x57)) { // W
		camera.rotateUpDown(lSpeedHorizontal);
	}

	if (GetAsyncKeyState(0x53)) { // ?
		camera.rotateUpDown(-lSpeedVertical);
	}

	if (GetAsyncKeyState(0x41)) { // ?
		camera.rotateLeftRight(lSpeedHorizontal);
	}

	if (GetAsyncKeyState(0x44)) { // ?
		camera.rotateLeftRight(-lSpeedHorizontal);
	}

	if (GetAsyncKeyState(0x45)) { // ?
		camera.zoomInOut(lSpeedZoom);
	}

	if (GetAsyncKeyState(0x51)) { // ?
		camera.zoomInOut(-lSpeedZoom);
	}

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