<<<<<<< HEAD
#pragma once

#include "../../General_Heading.h"

#include <vector>
#include <string>
#include "map"

#include "../../Data/Data.h"
#include "GameObject.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;


// ����������� ����� ������� �������� 
enum class GameObjectType {
	LIGHT_OBJECT, // ������ ������� ������
	HEAVY_OBJECT, // ������� ������� ������
	BORDER_OBJECT, // ��������� ������� ������
	PLAYER, // ������� ������ ��� ������������� ������
	BOMB, // ������� ������ ��� ������������� �����
	MONSTER // ������� ������ ��� ������������� ��������
};

// ����� ��� �������� ������� ��������
class GameObjectFactory
{
public:
	// ������������� ������� (�������� ����� � ��������� ���������� ���������)
	void init(std::string filename);
	// �������� ������ ������� ��������� ����
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y, int z = 0);
private:
	// ���� ��� ������� ���� �������
	std::vector<std::shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	std::vector<std::shared_ptr<Material>> materials;
=======
#pragma once

#include "../../General_Heading.h"

#include <vector>
#include <string>
#include "map"

#include "../../Data/Data.h"
#include "GameObject.h"
#include "rapidjson/document.h"

using namespace rapidjson;
using namespace std;


// ����������� ����� ������� �������� 
enum class GameObjectType {
	LIGHT_OBJECT, // ������ ������� ������
	HEAVY_OBJECT, // ������� ������� ������
	BORDER_OBJECT, // ��������� ������� ������
	PLAYER, // ������� ������ ��� ������������� ������
	BOMB, // ������� ������ ��� ������������� �����
	MONSTER // ������� ������ ��� ������������� ��������
};

// ����� ��� �������� ������� ��������
class GameObjectFactory
{
public:
	// ������������� ������� (�������� ����� � ��������� ���������� ���������)
	void init(std::string filename);
	// �������� ������ ������� ��������� ����
	std::shared_ptr<GameObject> create(GameObjectType type, int x, int y, int z = 0);
private:
	// ���� ��� ������� ���� �������
	std::vector<std::shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	std::vector<std::shared_ptr<Material>> materials;
>>>>>>> 1f562be79d16193a9746e34b908252d6844f6415
};