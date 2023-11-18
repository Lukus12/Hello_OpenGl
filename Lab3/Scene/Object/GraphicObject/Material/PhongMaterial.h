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

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial : public Material
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
	void load(MaterialParams value);
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

// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial : public Material
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
	void load(MaterialParams value);
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
>>>>>>> 1f562be79d16193a9746e34b908252d6844f6415
};