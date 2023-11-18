#include "Camera.h"
#define CORRECTION 3.14159265 / 180
void Camera::recalculatePosition()
{
	position[0] = r * sin(angleY * CORRECTION) * cos(angleX * CORRECTION);
	position[2] = r * sin(angleY * CORRECTION) * sin(angleX * CORRECTION);
	position[1] = r * cos(angleY * CORRECTION);
}

Camera::Camera() :Camera(vec3())
{

}

Camera::Camera(vec3 position)
{
	setPosition(position);
}

Camera::Camera(float x, float y, float z) :Camera(vec3(x, y, z))
{

}

void Camera::setPosition(vec3 position)
{
	this->position[0] = position.x;
	this->position[1] = position.y;
	this->position[2] = position.z;
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}

vec3 Camera::getPosition() {
	return this->position;
}

void Camera::rotateLeftRight(float degree)
{
	angleX += degree;
	if (angleX > 360) angleX -= 360;
	if (angleX < 360) angleX += 360;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
	angleY -= degree;
	if (angleY > 179) angleY -= 1;
	if (angleY < 1) angleY += 1;
	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	r -= distance;
	recalculatePosition();
}

void Camera::apply()
{
	gluLookAt(position[0], position[1], position[2], 0, 0, 0, 0, 1, 0);
}