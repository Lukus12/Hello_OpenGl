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

#include "PhongMaterial.h"

using namespace glm;
using namespace std;
// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject
{
public:
	GraphicObject();
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
	void setMaterial(PhongMaterial* material);
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
	PhongMaterial* material;
private:
	// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};
