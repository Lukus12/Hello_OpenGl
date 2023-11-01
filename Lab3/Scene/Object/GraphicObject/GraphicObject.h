#pragma once
#include <windows.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material/PhongMaterial.h"
#include "Mesh/Mesh.h"

using namespace glm;
using namespace std;
// ����� ��� ������������� ������ ������������ �������
class GraphicObject
{
public:
	// ��������� � ��������� ������� �������
	void setPosition(vec3 position);
	vec3 getPosition();
	// ��������� � ��������� ���� �������� � ��������
	// ������� �������������� � �������������� ��������� 
	// ������ ��� Oy �� ������� �������
	void setAngle(float grad);
	float getAngle();
	// ��������� �������� ����� �������
	void set�olor(vec3 color);
	vec3 getColor();
	// ��������� ������������� ���������
	void setMaterial(const vector<shared_ptr<PhongMaterial>>& material);
	// ��������� ������������� ����
	void setMesh(shared_ptr<Mesh> mesh);
	// ������� ������
	void draw();
private:
	// ������� ������� � ���������� ������� ���������
	vec3 position;
	// ���� �������� � �������������� ��������� (� ��������)
	float angle;
	// ���� ������
	vec3 color;
	// ������� ������ (������������ �������) - ���� �� ��������� ������ ���
	mat4 modelMatrix;
	// ������������ ��������
	vector<shared_ptr<PhongMaterial>> material;
	// ������������ ���
	shared_ptr<Mesh> mesh;

private:
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();
};
