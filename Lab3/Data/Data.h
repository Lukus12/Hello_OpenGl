#pragma once

#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include "..\Scene\Camera\Camera.h"
#include "..\Scene\Lighting\Light.h"
#include "..\Scene\Object\GraphicObject.h"
#include <sstream>
//#include "PhongMaterial.h"

// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
// используемая камера
extern Camera camera;
// источник света
extern Light light;



extern LARGE_INTEGER current, previous, frequency, end;

