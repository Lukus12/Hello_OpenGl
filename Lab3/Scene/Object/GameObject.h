#pragma once

#include <windows.h>

#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "..\Object\GraphicObject\GraphicObject.h"

// ����� ��� ������������� �������� �������
class GameObject
{
public:
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(shared_ptr<GraphicObject> graphicObject);
	// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
	void setPosition(int x, int y);
	void setPosition(int x, int y, float z);
	void setPosition(ivec2 position);
	
	void CreatGameObject();
	// ��������� ������� ���������� ���������
	ivec2 getPosition();
	// ����� �������� ������� �� �����
	void draw(void);
private:
	// ���������� ���������� �������� �������
	ivec2 position;
	// ����������� ������ (��� ������ �� �����)
	shared_ptr<GraphicObject> graphicObject;
};