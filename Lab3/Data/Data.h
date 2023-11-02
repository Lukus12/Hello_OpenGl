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


// ������ ����������� ��������
extern std::vector<shared_ptr<GraphicObject>>graphicObjects;
// ������������ ������
extern Camera camera;
// �������� �����
extern Light light1;
extern Light light2;
extern Light light3;
extern Light light4;
extern Light light5;
//struct Vertex;

extern int passabilityMap[21][21];
extern shared_ptr<GameObject> mapObjects[21][21];

extern LARGE_INTEGER current, previous, frequency, end;

// ������������ ���������
extern std::vector<shared_ptr<PhongMaterial>> materials;
// ������������ ����
extern std::vector<shared_ptr<Mesh>> meshes;
extern shared_ptr<Mesh> meshPole;
extern shared_ptr<Mesh> meshBox;
extern shared_ptr<Mesh> meshChamferBox;
extern shared_ptr<Mesh> meshSphere;
