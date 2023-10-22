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

// ������ ����������� ��������
extern std::vector<GraphicObject> graphicObjects;
// ������������ ������
extern Camera camera;
// �������� �����
extern Light light;

//extern PhongMaterial material;

extern LARGE_INTEGER current, previous, frequency, end;
extern double interval, fps;
extern int frameCount;

extern GraphicObject obj1;
extern GraphicObject obj2;
extern GraphicObject obj3;
extern GraphicObject obj4;
