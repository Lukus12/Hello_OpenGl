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

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial
{
public:
	// конструктор по умолчанию
	// 
	//PhongMaterial(string filename, int flag);
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);
	void load(Material value);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая 
	vec4 ambient;
	// диффузная составляющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
};