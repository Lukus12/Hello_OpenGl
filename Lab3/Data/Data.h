#pragma once

#include <vector>

#include "..\Scene\Camera\Camera.h"
#include "..\Scene\Object\GameObjectFactory.h"
#include "..\Scene\Lighting\Light.h"
#include "..\Scene\Object\GraphicObject\GraphicObject.h"
#include "..\Scene\Object\GameObject.h"


// список графических объектов
extern std::vector<shared_ptr<GraphicObject>>graphicObjects;
// игровые объекты
extern std::shared_ptr<GameObject> player;
extern std::shared_ptr<GameObject> monsters[5];
extern std::shared_ptr<GameObject> bomb;
// прошлый путь монстра и сбор направления
extern MoveDirection lastDirection[5];
extern int blockDirection[5];
// поле
extern GameObject field;
// используемая камера
extern Camera camera;
// источник света
extern Light light;

extern Texture planeTexture;

extern int passabilityMap[21][21];
extern shared_ptr<GameObject> mapObjects[21][21];

extern LARGE_INTEGER current, previous, frequency, end;


void initData();
