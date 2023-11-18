
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;
float limitTime;

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
		if (passabilityMap[nextPlayerPosX][nextPlayerPosY - 1] == 0) {
			(*player).move(MoveDirection::UP, 50);
		}
		else if (passabilityMap[nextPlayerPosX][nextPlayerPosY - 1] == 1 &&
			(passabilityMap[nextPlayerPosX][nextPlayerPosY - 2] == 0)) {
				moveLightBox(MoveDirection::UP, nextPlayerPosX, nextPlayerPosY);
		}
	}
	if (GetAsyncKeyState('S')) {
		if (passabilityMap[nextPlayerPosX][nextPlayerPosY + 1] == 0) {
			(*player).move(MoveDirection::DOWN, 50);
		}
		else if (passabilityMap[nextPlayerPosX][nextPlayerPosY + 1] == 1 &&
			(passabilityMap[nextPlayerPosX][nextPlayerPosY + 2] == 0)) {
				moveLightBox(MoveDirection::DOWN, nextPlayerPosX, nextPlayerPosY);
		}
	}
	if (GetAsyncKeyState('A')){
		if (passabilityMap[nextPlayerPosX - 1][nextPlayerPosY] == 0) {
			(*player).move(MoveDirection::LEFT, 50);
		}
		else if (passabilityMap[nextPlayerPosX - 1][nextPlayerPosY] == 1 &&
			(passabilityMap[nextPlayerPosX - 2][nextPlayerPosY] == 0)) {
				moveLightBox(MoveDirection::LEFT, nextPlayerPosX, nextPlayerPosY);
		}
	}
	if (GetAsyncKeyState('D')){
		if (passabilityMap[nextPlayerPosX + 1][nextPlayerPosY] == 0) {
			(*player).move(MoveDirection::RIGHT, 50);
		}
		else if (passabilityMap[nextPlayerPosX + 1][nextPlayerPosY] == 1 &&
			(passabilityMap[nextPlayerPosX + 2][nextPlayerPosY] == 0)) {
				moveLightBox(MoveDirection::RIGHT, nextPlayerPosX, nextPlayerPosY);
		}
	}
}

void randomizeDirection(MoveDirection &direction)
{
	int randNum = rand() % 5;
	switch (randNum) {
		case 1:
			direction = MoveDirection::LEFT;
			break;
		case 2:
			direction = MoveDirection::RIGHT;
			break;
		case 3:
			direction = MoveDirection::UP;
			break;
		case 4:
			direction = MoveDirection::DOWN;
			break;
	}
}


void monstersSimulation(float simulationTime)
{
	MoveDirection direction = MoveDirection::STOP;
	limitTime += simulationTime*50;

	if (limitTime >= 0.1) {
		limitTime = 0;
		for (int i = 0; i < 5; i++) {

			if (player != nullptr) {
				if ((*monsters[i]).getPosition() == (*player).getPosition()) {
					player.reset();
				}
			}

			/*
					Выбираем рандом направление, если там не 0, выбираем по новой,
				иначе идем по выбранному направлению и сохраняем прошлое направление
				прошлое направление противоположно текущему
				прошлое направление меняется, когда монстр выбирает путь отличный от текущего
			*/

			if (!(*monsters[i]).isMoving()) {

				randomizeDirection(direction);

				int monsterPositionX = (*monsters[i]).getPosition()[0];
				int monsterPositionY = (*monsters[i]).getPosition()[1];

				ivec2 nextMonsterPosition;
				nextMonsterPosition.x = monsterPositionX;
				nextMonsterPosition.y = monsterPositionY;

				switch (direction) {
					case MoveDirection::LEFT:
						nextMonsterPosition.x--;
						break;
					case MoveDirection::RIGHT:
						nextMonsterPosition.x++;
						break;
					case MoveDirection::UP:
						nextMonsterPosition.y--;
						break;
					case MoveDirection::DOWN:
						nextMonsterPosition.y++;
						break;
				}

				int typeNextPosition = passabilityMap[nextMonsterPosition.x][nextMonsterPosition.y];

				//проверка на тупик
				blockDirection[i]++;
				if (blockDirection[i] == 100) {
					lastDirection[i] = {};
					blockDirection[i] = 0;
				}

				if (typeNextPosition == 0 and direction != lastDirection[i]) {

					(*monsters[i]).move(direction, 50);
					passabilityMap[monsterPositionX][monsterPositionY] = 0;
					passabilityMap[nextMonsterPosition.x][nextMonsterPosition.y] = 2;

					//сохр путь отуда пришёл монстр
					switch (direction) {
						case MoveDirection::LEFT:
							lastDirection[i] = MoveDirection::RIGHT;
							break;
						case MoveDirection::RIGHT:
							lastDirection[i] = MoveDirection::LEFT;
							break;
						case MoveDirection::UP:
							lastDirection[i] = MoveDirection::DOWN;
							break;
						case MoveDirection::DOWN:
							lastDirection[i] = MoveDirection::UP;
							break;
					}
				}
			}
		}
	}
}


void gameObjectSimulation(float simulationTime) {
	if (player != nullptr) {
		(*player).simulate(simulationTime);
	}
	for (int i = 0; i < 5; i++) {
		(*monsters[i]).simulate(simulationTime);
	}
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (passabilityMap[i][j] == 1) {
				(*mapObjects[i][j]).simulate(simulationTime);
			}
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
	//перемещение монстров
	monstersSimulation(simulationTime);
	//перемещение главного героя
	if (player != nullptr) {
		movePlayer();
	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};