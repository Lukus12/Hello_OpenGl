#pragma once

#include "../../General_Heading.h"

#include "..\Object\GraphicObject\GraphicObject.h"

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ИГРОВОГО ОБЪЕКТА
class GameObject
{
public:
	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(shared_ptr<GraphicObject> graphicObject);
	// установка логических координат (два перегруженных метода для удобства)
	void setPosition(int x, int y);
	void setPosition(int x, int y, float z);
	void setPosition(ivec2 position);
	
	void CreatGameObject();
	// получение текущих логических координат
	ivec2 getPosition();
	// вывод игрового объекта на экран
	void draw(void);
private:
	// логические координаты игрового объекта
	ivec2 position;
	// графический объект (для вывода на экран)
	shared_ptr<GraphicObject> graphicObject;
};