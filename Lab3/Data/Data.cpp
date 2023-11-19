#include "Data.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;

LARGE_INTEGER previous, frequency;

// ������� ��� �������� ������� ��������
GameObjectFactory gameObjectFactory;

// ������� ���� ������� � ����� �����������
MoveDirection lastDirection[5] = {};
int blockDirection[5] = {};

// ������ ����������� ��������
vector<shared_ptr<GraphicObject>>graphicObjects;
// ������ ������� �������� ������������� �� �����
shared_ptr<GameObject> mapObjects[21][21];
// ���� 
GameObject field;
// �����
shared_ptr<GameObject> player;
// �������
shared_ptr<GameObject> monsters[5];
// �����
shared_ptr<GameObject> bomb;
// ������������ ������
Camera camera(0.1, 0.1, 50);

// �������� �����
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

	// ������������� ������� (� ���������� �� ������ json-�����)
	gameObjectFactory.init("Data//GameObjectsDescription.json");

	// ������� ����
	shared_ptr<GraphicObject> Pole = shared_ptr<GraphicObject>(new GraphicObject());
	Pole->setPosition(vec3(0, -0.51, 0));

	// ��������� ���� ��� ���������
	shared_ptr<Mesh> meshPole = make_shared<Mesh>();
	meshPole->load("Data//meshes//SimplePlane.obj");
	Pole->setMesh({ meshPole });

	// �������� �������� ��� ���������
	shared_ptr<Texture> planeTexture = make_shared<Texture>();
	planeTexture->load("Data//textures//plane.jpg");

	// ��������� ��������� ��� ���������
	shared_ptr<PhongMaterialWithTexture> planeMaterial = make_shared<PhongMaterialWithTexture>();
	planeMaterial->load("Data//materials//PlaneMaterial.txt");
	planeMaterial->setTexture(planeTexture);
	Pole->setMaterial({ planeMaterial });
	graphicObjects.push_back(Pole);

	field.setGraphicObject(graphicObjects.back());

	//�����
	player = gameObjectFactory.create(GameObjectType::PLAYER, 1, 19);

	// �������
	ivec2 monsterLocation[5]{ ivec2(5, 3), ivec2(19, 5), ivec2(19, 18), ivec2(1, 15), ivec2(9, 9) };

	for (int i = 0; i < 5; i++) {
		monsters[i] = gameObjectFactory.create(GameObjectType::MONSTER, monsterLocation[i].x, monsterLocation[i].y);
	}

	//�����
	bomb = nullptr;

	// ������������� �������� �����
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








