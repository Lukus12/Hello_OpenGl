
#include "Simulation.h"


extern LARGE_INTEGER previous, frequency;


void moveCamera(float simulationTime) {
	// ������� ����� �� ����
	// l - local
	float lSpeedHorizontal = 130 * simulationTime;
	float lSpeedVertical = 130 * simulationTime;
	float lSpeedZoom = 20 * simulationTime;

	// ������ ������ �� ���������, � �� �� ���������
	// ��� ���� ��������� ����������,
	// �� ����� �������, ��� ������ 0x57 � �.�.
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
	// ����������� ������� ���������
	double simulationTime = getSimulationTime();
	//std::cout << simulationTime << "\n";
	// ������������ ������
	moveCamera(simulationTime);

	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
};