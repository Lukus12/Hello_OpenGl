#include "Data.h"

// используемые пространства имен
using namespace glm;
using namespace std;

LARGE_INTEGER previous, frequency;

// список графических объектов
vector<shared_ptr<GraphicObject>>graphicObjects;
// список игровых объектов расположенных на карте
shared_ptr<GameObject> mapObjects[21][21];
// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;
// игрок
shared_ptr<GameObject> player;
// используемая камераы
Camera camera(2, 2, 2);

// источник света
Light light1(-15, 10, 10);
/*Light light1(0, 10, 0);
Light light2(25, 10, 0);
Light light3(0, 10, 25);
Light light4(-25, 10, 0);
Light light5(0, 10, -25);*/



void initData()
{

	shared_ptr<PhongMaterial> material = make_shared<PhongMaterial>();
	material->load("Data//materials//material_2.txt");

	shared_ptr<Mesh> meshBox = make_shared<Mesh>();
	meshBox->load("Data//meshes//Box.obj");

	shared_ptr<Mesh> meshHighPolyBox = make_shared<Mesh>();
	meshHighPolyBox->load("Data//meshes//HighPolyChamferBox.obj");

	shared_ptr<Mesh> meshFace = make_shared<Mesh>();
	meshFace->load("Data//meshes//Face.obj");

	shared_ptr<Mesh> meshCharacter = make_shared<Mesh>();
	meshCharacter->load("Data//meshes//Character.obj");

	shared_ptr<GraphicObject> Box = shared_ptr<GraphicObject>(new GraphicObject());
	Box->setPosition(vec3(0, 0, -1));
	Box->setMesh({ meshBox });
	graphicObjects.push_back(Box);

	shared_ptr<GraphicObject> HighPolyBox = shared_ptr<GraphicObject>(new GraphicObject());
	HighPolyBox->setPosition(vec3(0, 0, 0.5));
	HighPolyBox->setMesh({ meshHighPolyBox });
	graphicObjects.push_back(HighPolyBox);
	
	/*shared_ptr<GraphicObject> Face = shared_ptr<GraphicObject>(new GraphicObject());
	Face->setPosition(vec3(0, -0.2, 0));
	Face->setMesh({ meshFace });
	graphicObjects.push_back(Face);*/

	/*shared_ptr<GraphicObject> Character = shared_ptr<GraphicObject>(new GraphicObject());
	Character->setPosition(vec3(0, -0.5, 0));
	Character->setMesh({ meshCharacter });
	graphicObjects.push_back(Character);*/

	

}








