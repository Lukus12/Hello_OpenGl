#pragma once

#include <vector>

#include "..\Scene\Camera\Camera.h"
#include "..\Scene\Object\GameObjectFactory.h"
#include "..\Scene\Lighting\Light.h"
#include "..\Scene\Object\GraphicObject\GraphicObject.h"
#include "..\Scene\Object\GameObject.h"


// ������ ����������� ��������
extern std::vector<shared_ptr<GraphicObject>>graphicObjects;
// ������� �������
extern std::shared_ptr<GameObject> player;
extern std::shared_ptr<GameObject> monsters[5];
extern std::shared_ptr<GameObject> bomb;
// ������� ���� ������� � ���� �����������
extern MoveDirection lastDirection[5];
extern int blockDirection[5];
// ����
extern GameObject field;
// ������������ ������
extern Camera camera;
// �������� �����
extern Light light;

extern Texture planeTexture;

extern int passabilityMap[21][21];
extern shared_ptr<GameObject> mapObjects[21][21];

extern LARGE_INTEGER current, previous, frequency, end;


void initData();
