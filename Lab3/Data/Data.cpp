#include "Data.h"

// используемые пространства имен
using namespace glm;
using namespace std;

LARGE_INTEGER previous, frequency;

// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;

// прошлый путь монстра и сброс направления
MoveDirection lastDirection[5] = {};
int blockDirection[5] = {};

// список графических объектов
vector<shared_ptr<GraphicObject>>graphicObjects;
// список игровых объектов расположенных на карте
shared_ptr<GameObject> mapObjects[21][21];
// поле 
GameObject field;
// игрок
shared_ptr<GameObject> player;
// монстры
shared_ptr<GameObject> monsters[5];
// бомба
shared_ptr<GameObject> bomb;
// используемая камера
Camera camera(0.1, 0.1, 50);

// источник света
Light light(0,10,0);

Texture planeTexture;


int passabilityMap[21][21] = {
 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
 3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
 3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
 3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
 3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
 3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
 3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
 3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
 3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
 3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
 3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
 3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
 3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
 3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
 3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
 3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
 3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
 3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
 3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};



void initData()
{
	//planeTexture.load("Data//textures//plane.jpg");

	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("Data//GameObjectsDescription.json");

	// игровое поле
	shared_ptr<GraphicObject> Pole = shared_ptr<GraphicObject>(new GraphicObject());
	Pole->setPosition(vec3(0, -0.51, 0));

	// установка меша для плоскости
	shared_ptr<Mesh> meshPole = make_shared<Mesh>();
	meshPole->load("Data//meshes//SimplePlane.obj");
	Pole->setMesh({ meshPole });

	// загрузка текстуры для плоскости
	shared_ptr<Texture> planeTexture = make_shared<Texture>();
	planeTexture->load("Data//textures//plane.jpg");

	// установка материала для плоскости
	shared_ptr<PhongMaterialWithTexture> planeMaterial = make_shared<PhongMaterialWithTexture>();
	planeMaterial->load("Data//materials//PlaneMaterial.txt");
	planeMaterial->setTexture(planeTexture);
	Pole->setMaterial({ planeMaterial });
	graphicObjects.push_back(Pole);

	field.setGraphicObject(graphicObjects.back());

	//игрок
	player = gameObjectFactory.create(GameObjectType::PLAYER, 1, 19);

	// монстры
	ivec2 monsterLocation[5]{ ivec2(5, 3), ivec2(19, 5), ivec2(19, 18), ivec2(1, 15), ivec2(9, 9) };

	for (int i = 0; i < 5; i++) {
		monsters[i] = gameObjectFactory.create(GameObjectType::MONSTER, monsterLocation[i].x, monsterLocation[i].y);
	}

	//бомба
	bomb = nullptr;

	// инициализация объектов сцены
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		passabilityMap[monsterLocation[i].x][monsterLocation[i].y] = 5;
	}

}








