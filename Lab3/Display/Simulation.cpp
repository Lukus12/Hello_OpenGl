
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;

void moveLightBox(MoveDirection direction, int PlayerPosX, int PlayerPosY) {
	ivec2 offset = {};
	ivec2 newPos = {};
	ivec2 newPosBox = {};
	switch (direction) {
		case MoveDirection::STOP:
			offset = ivec2(0, 0);
			break;
		case MoveDirection::LEFT:
			offset = ivec2(-1, 0);
			break;
		case MoveDirection::RIGHT:
			offset = ivec2(1, 0);
			break;
		case MoveDirection::UP:
			offset = ivec2(0, -1);
			break;
		case MoveDirection::DOWN:
			offset = ivec2(0, 1);
			break;
	}
	newPos.x = offset.x + PlayerPosX;
	newPos.y = offset.y + PlayerPosY;

	newPosBox.x = offset.x*2 + PlayerPosX;
	newPosBox.y = offset.y*2 + PlayerPosY;

	(*player).move(direction, 25);
	(*mapObjects[newPos.x][newPos.y]).move(direction, 25);

	if ((*mapObjects[newPos.x][newPos.y]).isMoving() == false) {
		// смещаем свойства вслед за кубиком
		passabilityMap[newPos.x][newPos.y] = 0;
		passabilityMap[newPosBox.x][newPosBox.y] = 1;

		mapObjects[newPosBox.x][newPosBox.y] = mapObjects[newPos.x][newPos.y];
		mapObjects[newPos.x][newPos.y] = nullptr;
	}
}

void movePlayer() {
	vec2 nextPlayerPos = (*player).getPosition();
	int nextPlayerPosX = nextPlayerPos[0];
	int nextPlayerPosY = nextPlayerPos[1];

	if (GetAsyncKeyState('W')){
		/*cout << "X: " << nextPlayerPosX << " Y: " << nextPlayerPosY << endl;
		cout << passabilityMap[nextPlayerPosX][nextPlayerPosY - 1] << endl;*/

		if (passabilityMap[nextPlayerPosX][nextPlayerPosY - 1] == 0) {
			(*player).move(MoveDirection::UP, 50);
		}
		else if (passabilityMap[nextPlayerPosX][nextPlayerPosY - 1] == 1 &&
			(passabilityMap[nextPlayerPosX][nextPlayerPosY - 2] == 0)) {
				moveLightBox(MoveDirection::UP, nextPlayerPosX, nextPlayerPosY);
		}
	}
	if (GetAsyncKeyState('S')) {
		/*cout << "X: " << nextPlayerPosX << " Y: " << nextPlayerPosY << endl;
		cout << passabilityMap[nextPlayerPosX][nextPlayerPosY + 1] << endl;*/

		if (passabilityMap[nextPlayerPosX][nextPlayerPosY + 1] == 0) {
			(*player).move(MoveDirection::DOWN, 50);
		}
		else if (passabilityMap[nextPlayerPosX][nextPlayerPosY + 1] == 1 &&
			(passabilityMap[nextPlayerPosX][nextPlayerPosY + 2] == 0)) {
				moveLightBox(MoveDirection::DOWN, nextPlayerPosX, nextPlayerPosY);
		}
	}
	if (GetAsyncKeyState('A')){
		/*cout << "X: " << nextPlayerPosX << " Y: " << nextPlayerPosY << endl;
		cout << passabilityMap[nextPlayerPosX - 1][nextPlayerPosY] << endl;*/

		if (passabilityMap[nextPlayerPosX - 1][nextPlayerPosY] == 0) {
			(*player).move(MoveDirection::LEFT, 50);
		}
		else if (passabilityMap[nextPlayerPosX - 1][nextPlayerPosY] == 1 &&
			(passabilityMap[nextPlayerPosX - 2][nextPlayerPosY] == 0)) {
				moveLightBox(MoveDirection::LEFT, nextPlayerPosX, nextPlayerPosY);
		}
	}
	if (GetAsyncKeyState('D')){
		/*cout << "X: " << nextPlayerPosX << " Y: " << nextPlayerPosY << endl;
		cout << passabilityMap[nextPlayerPosX + 1][nextPlayerPosY] << endl;*/

		if (passabilityMap[nextPlayerPosX + 1][nextPlayerPosY] == 0) {
			(*player).move(MoveDirection::RIGHT, 50);
		}
		else if (passabilityMap[nextPlayerPosX + 1][nextPlayerPosY] == 1 &&
			(passabilityMap[nextPlayerPosX + 2][nextPlayerPosY] == 0)) {
				moveLightBox(MoveDirection::RIGHT, nextPlayerPosX, nextPlayerPosY);
		}
	}
}

void gameObjectSimulation(float simulationTime) {
	(*player).simulate(simulationTime);
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (passabilityMap[i][j] == 1) (*mapObjects[i][j]).simulate(simulationTime);
		}
	}
}

void moveCamera(float simulationTime)
{
	float SpeedHorizontal = 1300 * simulationTime;
	float SpeedVertical = 1300 * simulationTime;
	float SpeedZoom = 200 * simulationTime;

	if(GetAsyncKeyState(VK_UP)) camera.rotateUpDown(SpeedVertical);
	if (GetAsyncKeyState(VK_DOWN)) camera.rotateUpDown(-SpeedVertical);
	if (GetAsyncKeyState(VK_LEFT)) camera.rotateLeftRight(SpeedHorizontal);
	if (GetAsyncKeyState(VK_RIGHT)) camera.rotateLeftRight(-SpeedHorizontal);
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
	// передвижение камеры
	moveCamera(simulationTime);
	//симуляция всех игровых объектов (их плавное перемещение)
	gameObjectSimulation(simulationTime);
	//перемещение главного героя
	movePlayer();
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};