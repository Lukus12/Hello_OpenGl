#pragma once
#include <Windows.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include "map"

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "C:\Lessons\АОРГ\Lab3\Lab3\Data\Data.h"
#include "GameObject.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;


// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ 
enum class GameObjectType {
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	BOMB, // игровой объект для представления бомбы
	MONSTER // игровой объект для представления монстров
};

// КЛАСС ДЛЯ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ
class GameObjectFactory
{
public:
	// инициализация фабрики (загрузка мешей и установка параметров материала)
	void init(std::string filename);
	// создание нового объекта заданного типа
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y, int z = 0);
private:
	// меши для каждого типа объекта
	std::vector<std::shared_ptr<Mesh>> meshes;
	// материалы для каждого типа объекта
	std::vector<std::shared_ptr<PhongMaterial>> materials;
};