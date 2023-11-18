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
// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
public:
	// Установка и получение позиции объекта
	void setPosition(vec3 position);
	vec3 getPosition();
	// Установка и получения угла поворота в градусах
	// поворот осуществляется в горизонтальной плоскости 
	// вокруг оси Oy по часовой стрелке
	void setAngle(float grad);
	float getAngle();
	// Установка текущего цвета объекта
	void setСolor(vec3 color);
	vec3 getColor();
	// Установка используемого материала
	void setMaterial(const vector<shared_ptr<Material>>& material);
	// Установка используемого меша
	void setMesh(shared_ptr<Mesh> mesh);
	// Вывести объект
	void draw();
private:
	// Позиция объекта в глобальной системе координат
	vec3 position;
	// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;
	// Цвет модели
	vec3 color;
	// Матрица модели (расположение объекта) - чтоб не вычислять каждый раз
	mat4 modelMatrix;
	// Используемый материал
	vector<shared_ptr<Material>> material;
	// Используемый меш
	shared_ptr<Mesh> mesh;
private:
	// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};
