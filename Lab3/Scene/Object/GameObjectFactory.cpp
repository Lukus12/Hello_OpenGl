#include "GameObjectFactory.h"

using namespace std;
using namespace glm;
using namespace rapidjson;

void GameObjectFactory::init()
{
	for (int i = 0; i < 4; i++) {
		shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
		if (i == 0) material->load("Data//materials//material_2.txt");
		if (i == 1) material->load("Data//materials//material_3.txt");
		if (i == 2) material->load("Data//materials//material_4.txt");
		if (i == 3) material->load("Data//materials//material_Player.txt");
		//if (i == 3) material->load("Data//materials//material_5.txt");
		materials.push_back(material);
	}

	for (int i = 0; i < 4; i++) {
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		if (i >=0 and i<=2) mesh->load("Data//meshes//Box.obj");
		if (i == 3) mesh->load("Data//meshes//Sphere.obj");
		meshes.push_back(mesh);
	}

}

std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y, int z)
{
	int index{};
	switch (type)
	{
	case GameObjectType::BORDER_OBJECT:
		index = 2;
		break;
	case GameObjectType::HEAVY_OBJECT:
		index = 1;
		break;
	case GameObjectType::LIGHT_OBJECT:
		index = 0;
		break;
	case GameObjectType::MONSTER:
		index = 4;
		break;
	case GameObjectType::PLAYER:
		index = 3;
		break;
	}
	
	shared_ptr<GraphicObject> GrafObj = shared_ptr<GraphicObject>(new GraphicObject());
	GrafObj->setMaterial({ materials[index] });
	GrafObj->setMesh(meshes[index]);
	graphicObjects.push_back(GrafObj);

	shared_ptr<GameObject> GameObj(new GameObject);
	(*GameObj).setGraphicObject(graphicObjects.back());
	(*GameObj).setPosition(vec3(y, x, z));
	(*GameObj).draw();

	return GameObj;
}

