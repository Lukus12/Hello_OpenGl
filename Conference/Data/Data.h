#pragma once

#include <windows.h>

#include <vector>
#include <sstream>

#include "GL/glew.h"

#include "GL/freeglut.h"

#include <glm/glm.hpp>

#include "..\Scene\Camera\Camera.h"
#include "..\Scene\Lighting\Light.h"
#include "..\Scene\Object\GraphicObject\GraphicObject.h"
#include "..\Scene\Object\GameObject.h"
#include "..\Scene\Object\GameObjectFactory.h"

// список графических объектов
extern std::vector<shared_ptr<GraphicObject>>graphicObjects;
extern std::shared_ptr<GameObject> player;
// используемая камера
extern Camera camera;
// источник света
extern Light light1;
extern Light light2;
extern Light light3;
extern Light light4;
extern Light light5;
//struct Vertex;

extern int passabilityMap[21][21];
extern shared_ptr<GameObject> mapObjects[21][21];

extern LARGE_INTEGER current, previous, frequency, end;

void initData();
