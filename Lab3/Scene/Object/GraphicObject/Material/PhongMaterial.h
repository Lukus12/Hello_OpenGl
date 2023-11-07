#pragma once

#include "../../General_Heading.h"

#include <thread>
#include <string>
#include <vector>

#include "rapidjson/document.h"

using namespace glm;
using namespace std;

struct Material {
	vec4 Diffuse;
	vec4 Ambient;
	vec4 Specular;
	vec4 Emission;
	float Shininess;
};

// ����� ��� ������ � ����������
class PhongMaterial
{
public:
	// ����������� �� ���������
	// 
	//PhongMaterial(string filename, int flag);
	// ������� ���������� ���������
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// �������� ���������� ��������� �� �������� ���������� �����
	void load(std::string filename);
	void load(Material value);
	// ��������� ���� ���������� ���������
	void apply();
private:
	// ������� ������������ 
	vec4 ambient;
	// ��������� ������������
	vec4 diffuse;
	// ���������� ������������
	vec4 specular;
	// ������������
	vec4 emission;
	// ������� ����������������
	float shininess;
};