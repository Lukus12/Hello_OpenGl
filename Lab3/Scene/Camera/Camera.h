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
	// ���������� ������� ������ ����� ���������
	void recalculatePosition();
private:
	// ������ � ���� ��������
	float r;
	float angleX;
	float angleY;
	// ������� ������
	vec3 position;
public:
	// ������������
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);
	// ��������� � ��������� ������� ������
	void setPosition(vec3 position);
	vec3 getPosition();
	//������� ��� ����������� ������
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);
	// ������� ��� ��������� ������� ������
	void apply();
};