
#include "Simulation.h"

extern LARGE_INTEGER previous, frequency;
float limitTimeMonstr;
float bombTime;

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
	ivec2 nextPlayerPos = (*player).getPosition();
	int playerPosX = nextPlayerPos.x;
	int playerPosY = nextPlayerPos.y;

	if (!(*player).isMoving() && GetAsyncKeyState(0x20) && bomb == nullptr) {
		bomb = gameObjectFactory.create(GameObjectType::BOMB, nextPlayerPos.x, nextPlayerPos.y);
		passabilityMap[nextPlayerPos.x][nextPlayerPos.y] = 4;
	}

	MoveDirection direction = {};

	if (GetAsyncKeyState('W')) direction = MoveDirection::UP;
	if (GetAsyncKeyState('S')) direction = MoveDirection::DOWN;
	if (GetAsyncKeyState('A')) direction = MoveDirection::LEFT;
	if (GetAsyncKeyState('D')) direction = MoveDirection::RIGHT;

	switch (direction) {
		case MoveDirection::LEFT:
			nextPlayerPos.x--;
			break;
		case MoveDirection::RIGHT:
			nextPlayerPos.x++;
			break;
		case MoveDirection::UP:
			nextPlayerPos.y--;
			break;
		case MoveDirection::DOWN:
			nextPlayerPos.y++;
			break;
	}

	if (!(*player).isMoving()) {
		int typeNextPosition = passabilityMap[nextPlayerPos.x][nextPlayerPos.y];
		if (typeNextPosition == 0) {
			(*player).move(direction, 50);
		}
		if (typeNextPosition == 1) {
			switch (direction) {
				case MoveDirection::LEFT:
					nextPlayerPos.x--;
					break;
				case MoveDirection::RIGHT:
					nextPlayerPos.x++;
					break;
				case MoveDirection::UP:
					nextPlayerPos.y--;
					break;
				case MoveDirection::DOWN:
					nextPlayerPos.y++;
					break;
			}
			int typeNext2Position = passabilityMap[nextPlayerPos.x][nextPlayerPos.y];
			if (typeNext2Position == 0) moveLightBox(direction, playerPosX, playerPosY);
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
	limitTimeMonstr += simulationTime*50;

	if (limitTimeMonstr >= 0.1) {
		limitTimeMonstr = 0;
		for (int i = 0; i < 5; i++) {
			if (monsters[i] != nullptr) {
				if (player != nullptr) {
					if ((*monsters[i]).getPosition() == (*player).getPosition()) {
						player.reset();
					}
				}

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

					//сброс пути (с расчётом на то, что монстр засрял в тупике)
					blockDirection[i]++;
					if (blockDirection[i] == 100) {
						lastDirection[i] = {};
						blockDirection[i] = 0;
					}

					if (typeNextPosition == 0 and direction != lastDirection[i]) {

						(*monsters[i]).move(direction, 50);
						passabilityMap[monsterPositionX][monsterPositionY] = 0;
						passabilityMap[nextMonsterPosition.x][nextMonsterPosition.y] = 5;

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
}

void bombSimulation(float simulationTime) {
	if (bomb != nullptr) {
		bombTime += simulationTime * 50;
		if (bombTime > 3.5) {
			bombTime = 0;
			ivec2 bombPosition = (*bomb).getPosition();
			passabilityMap[bombPosition.x][bombPosition.y] = 0;
			
			MoveDirection directions[4] = { MoveDirection::UP, MoveDirection::RIGHT, MoveDirection::DOWN, MoveDirection::LEFT };
			
			for (MoveDirection direction : directions) {
				
				ivec2 explosionRadius;
				explosionRadius.x = bombPosition.x;
				explosionRadius.y = bombPosition.y;

				switch (direction) {
					case MoveDirection::LEFT:
						explosionRadius.x--;
						break;
					case MoveDirection::RIGHT:
						explosionRadius.x++;
						break;
					case MoveDirection::UP:
						explosionRadius.y--;
						break;
					case MoveDirection::DOWN:
						explosionRadius.y++;
						break;
				}
				
				int typeNextPosition;
				
				for (int i = 0; i < 2; i++) {
					typeNextPosition = passabilityMap[explosionRadius.x][explosionRadius.y];
					if (typeNextPosition == 2 || typeNextPosition == 3) break;
					
					if (player != nullptr) {
						if ((*player).getPosition() == explosionRadius) {
							player.reset();
							break;
						}
					}
					
					if (typeNextPosition == 5) {
						for (auto& monster : monsters) {
							if (monster != nullptr) {
								if ((*monster).getPosition() == explosionRadius) {
									monster = nullptr;
								}
							}
						}
						passabilityMap[explosionRadius.x][explosionRadius.y] = 0;
						break;
					}
					if (typeNextPosition == 1) {
						mapObjects[explosionRadius.x][explosionRadius.y] = nullptr;
						passabilityMap[explosionRadius.x][explosionRadius.y] = 0;
						break;
					}
					switch (direction) {
						case MoveDirection::LEFT:
							explosionRadius.x--;
							break;
						case MoveDirection::RIGHT:
							explosionRadius.x++;
							break;
						case MoveDirection::UP:
							explosionRadius.y--;
							break;
						case MoveDirection::DOWN:
							explosionRadius.y++;
							break;
					}
				}
			}

			passabilityMap[bombPosition.x][bombPosition.y] = 0;
			bomb = nullptr;
		}
	}
}

void gameObjectSimulation(float simulationTime) {
	if (player != nullptr) {
		(*player).simulate(simulationTime);
	}
	for (int i = 0; i < 5; i++) {
		if (monsters[i] != nullptr) {
			(*monsters[i]).simulate(simulationTime);
		}
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
    // существование бомбы
	bombSimulation(simulationTime);
	//перемещение главного героя
	if (player != nullptr) {
		movePlayer();
	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
};