#include "Data.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;

LARGE_INTEGER previous, frequency;

// ������ ����������� ��������
vector<shared_ptr<GraphicObject>>graphicObjects;

// ������������ ������
Camera camera(20, 15, 27.5);

// �������� �����
Light light1(0,10,0);
Light light2(25, 10, 0);
Light light3(0, 10, 25);
Light light4(-25, 10, 0);
Light light5(0, 10, -25);
/*struct Vertex
{
	// �������������� ����������
	GLfloat coord[3];
	// ������ �������
	GLfloat normal[3];
	// ���������� ���������� �������� ����������� ����� 
	GLfloat texCoord[2];
};*/

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
// ������ ������� �������� ������������� �� �����
shared_ptr<GameObject> mapObjects[21][21];
// ������� ��� �������� ������� ��������
GameObjectFactory gameObjectFactory;
// �����
shared_ptr<GameObject> player;


void initData()
{

	//meshChamferBox->load("Data//meshes//ChamferBox.obj");

	/*

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {

			shared_ptr<GraphicObject> grafObj = shared_ptr<GraphicObject>(new GraphicObject());
			switch (passabilityMap[i][j]) {
			case 1:
				grafObj->setMaterial({ material2 });
				break;
			case 2:
				grafObj->setMaterial({ material3 });
				break;
			case 3:
				grafObj->setMaterial({ material4 });
				break;
			default:
				continue;
				//break;
			}
			grafObj->setMesh({ meshBox });
			graphicObjects.push_back(grafObj);

			GameObject gameObj;
			gameObj.setGraphicObject(graphicObjects.back());
			gameObj.setPosition(ivec2(j, i));
			gameObj.draw();
		}
	}*/
	// ������������� ������� (� ���������� �� ������ json-�����)
	gameObjectFactory.init();

	// ������� ����
	shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
	material->load("Data//materials//material_1.txt");

	shared_ptr<Mesh> meshPole = make_shared<Mesh>();
	meshPole->load("Data//meshes//SimplePlane.obj");

	shared_ptr<GraphicObject> Pole = shared_ptr<GraphicObject>(new GraphicObject());
	Pole->setPosition(vec3(0, -0.5, 0));
	Pole->setMaterial({ material });
	Pole->setMesh({ meshPole });
	graphicObjects.push_back(Pole);

	GameObject gamePole;
	gamePole.setGraphicObject(graphicObjects[0]);
	gamePole.draw();

	//�����
	player = gameObjectFactory.create(GameObjectType::PLAYER, 19, 1);

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

}








