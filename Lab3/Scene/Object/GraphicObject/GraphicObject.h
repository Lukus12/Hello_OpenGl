#pragma once

#include "../../General_Heading.h"

#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>

#include "Material/PhongMaterial.h"
#include "Mesh/Mesh.h"
#include "Texture/Texture.h"


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
	// ��������� ��������
	void setTexture(shared_ptr<Texture> texture);
	// ������� ������
	void draw();
	void drawPole();
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
	// ������������ �������� 
	shared_ptr<Texture> texture;
private:
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();
};
