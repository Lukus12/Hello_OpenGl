#pragma once

#include <windows.h>

#include "GL/glew.h"

#include <vector>

#include "GL/freeglut.h"

#include <glm/glm.hpp>

#include "../Object/GraphicObject/GraphicObject.h"

class Camera
{
private:
	// перерасчет позиции камеры после поворотов
	void recalculatePosition();
private:
	// радиус и углы поворота
	float r;
	float angleX;
	float angleY;
	// позиция камеры
	vec3 position;
public:
	// конструкторы
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);
	// установка и получение позиции камеры
	void setPosition(vec3 position);
	vec3 getPosition();
	//функции для перемещения камеры
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);
	// функция для установки матрицы камеры
	void apply();
};