<<<<<<< HEAD
#pragma once

#include "../../General_Heading.h"

#include <thread>
#include <string>
#include <vector>

#include "rapidjson/document.h"

#include "Material.h"
#include "MaterialParams.h"

using namespace glm;
using namespace std;

// ����� ��� ������ � ����������
class PhongMaterialWithTexture : public Material
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
	void load(MaterialParams value);
	//��������� �������
	void setTexture(shared_ptr<Texture> texture);
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
	// ��������
	shared_ptr<Texture> texture;
=======
#pragma once

#include "../../General_Heading.h"

#include <thread>
#include <string>
#include <vector>

#include "rapidjson/document.h"

#include "Material.h"
#include "MaterialParams.h"

using namespace glm;
using namespace std;

// ����� ��� ������ � ����������
class PhongMaterialWithTexture : public Material
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
	void load(MaterialParams value);
	//��������� �������
	void setTexture(shared_ptr<Texture> texture);
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
	// ��������
	shared_ptr<Texture> texture;
>>>>>>> 1f562be79d16193a9746e34b908252d6844f6415
};