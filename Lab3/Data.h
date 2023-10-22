#pragma once

#include <windows.h>
#include <vector>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include "Camera.h"
#include "Light.h"
#include "GraphicObject.h"
#include <sstream>
//#include "PhongMaterial.h"

// список графических объектов
extern std::vector<GraphicObject> graphicObjects;
// используемая камера
extern Camera camera;
// источник света
extern Light light;

//extern PhongMaterial material;

extern LARGE_INTEGER current, previous, frequency, end;
extern double interval, fps;
extern int frameCount;

extern GraphicObject obj1;
extern GraphicObject obj2;
extern GraphicObject obj3;
extern GraphicObject obj4;
