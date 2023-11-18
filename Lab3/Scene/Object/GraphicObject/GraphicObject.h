#pragma once

#include "../../General_Heading.h"

#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>

#include "Material/Material.h"
#include "Material/PhongMaterial.h"
#include "Material/PhongMaterialWithTexture.h"
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
	void setMaterial(const vector<shared_ptr<Material>>& material);
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
	vector<shared_ptr<Material>> material;
	// ������������ ���
	shared_ptr<Mesh> mesh;
private:
	// ������ ������� modelMatrix �� ������ position � angle
	void recalculateModelMatrix();
};
