#include <windows.h>

#include "Scene\Object\GraphicObject\GraphicObject.h"
#include "Scene\Camera\Camera.h"
#include "Scene\Lighting\Light.h"
#include "Display\Display.h"
#include "Display\Simulation.h"
#include "Data\Data.h"
#include "Scene\Object\GraphicObject\Material\PhongMaterial.h"
#include "Scene\Object\GraphicObject\Mesh\Mesh.h"
#include "Scene\Object\GameObject.h"


#include <iostream>
#include <fstream>
#include <sstream>

#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// используем пространство имен стандартной библиотеки
using namespace std;
using namespace glm;

extern vector<GraphicObject> graphicObjects;
extern Camera camera;
//extern Light light;
extern LARGE_INTEGER previous, frequency;

vector<GameObject> GameObjects;

void main(int argc, char** argv)
{
	setlocale(LC_NUMERIC, "POSIX");
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(1280, 600);
	// 3. создаем окно
	glutCreateWindow("");
	glutSetWindowTitle("Laba_06 [ ]");
	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previous);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	shared_ptr<PhongMaterial> material1 = make_shared<PhongMaterial>();
	material1->load("Data//materials//material_1.txt");

	shared_ptr<PhongMaterial> material2 = make_shared<PhongMaterial>();
	material2->load("Data//materials//material_2.txt");

	shared_ptr<PhongMaterial> material3 = make_shared<PhongMaterial>();
	material3->load("Data//materials//material_3.txt");

	shared_ptr<PhongMaterial> material4 = make_shared<PhongMaterial>();
	material4->load("Data//materials//material_4.txt");

	mesh->load("Data//meshes//SimplePlane.obj");

	GraphicObject grafObj;
	grafObj.setPosition(vec3(-1, 0, 0));
	grafObj.setAngle(0);
	grafObj.setСolor(vec3(1, 0, 0));
	grafObj.setMaterial({ material1 });
	grafObj.setMesh({ mesh });
	graphicObjects.push_back(grafObj);


	/*GameObject gameObj;
	gameObj.setPosition(ivec2(10, 10));
	gameObj.setGraphicObject(graphicObjects[0]);
	gameObj.draw();*/
	
	
	glutIdleFunc(simulation);

	//включение механизма расчета освещения
	glEnable(GL_LIGHTING);
	GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	//Установка параметров источника света. 
	glEnable(GL_LIGHT0);


	// основной цикл обработки сообщений ОС
	glutMainLoop();
};


