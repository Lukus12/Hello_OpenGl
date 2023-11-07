#pragma once

#include "../../General_Heading.h"

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