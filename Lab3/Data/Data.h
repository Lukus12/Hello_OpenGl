#pragma once

#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include "..\Scene\Camera\Camera.h"
#include "..\Scene\Lighting\Light.h"
#include "..\Scene\Object\GraphicObject\GraphicObject.h"
#include "..\Scene\Object\GameObject.h"
#include <sstream>


// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
// используемая камера
extern Camera camera;
// источник света
extern Light light;

//struct Vertex;

extern int passabilityMap[21][21];
extern shared_ptr<GameObject> mapObjects[21][21];

extern LARGE_INTEGER current, previous, frequency, end;

// используемые материалы
extern std::vector<shared_ptr<PhongMaterial>> materials;
// используемые меши
extern std::vector<shared_ptr<Mesh>> meshes;
extern shared_ptr<Mesh> mesh;
