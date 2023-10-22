#include <windows.h>

#include "GraphicObject.h"
#include "Camera.h"
#include "Light.h"
#include "Display.h"
#include "Simulation.h"
#include "Data.h"
#include "PhongMaterial.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>

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
	glutSetWindowTitle("Laba_04 [ ]");
	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previous);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	PhongMaterial material;
	material.load("Data//materials//material_1.txt");

	extern GraphicObject obj1;
	obj1.setPosition(vec3(4, 0, 0));
	obj1.setAngle(180);
	obj1.setСolor(vec3(1, 0, 0));
	obj1.setMaterial(&material);
	graphicObjects.push_back(obj1);

	extern GraphicObject obj2;
	obj2.setPosition(vec3(-4, 0, 0));
	obj2.setAngle(0);
	obj2.setСolor(vec3(0, 0, 1));
	obj2.setMaterial(&material);
	graphicObjects.push_back(obj2);

	extern GraphicObject obj3;
	obj3.setPosition(vec3(0, 0, -4));
	obj3.setAngle(270);
	obj3.setСolor(vec3(0.2, 1, 0));
	obj3.setMaterial(&material);
	graphicObjects.push_back(obj3);
	
	extern GraphicObject obj4;
	obj4.setPosition(vec3(0, 0, 4));
	obj4.setAngle(90);
	obj4.setСolor(vec3(1, 1, 1));
	obj4.setMaterial(&material);
	graphicObjects.push_back(obj4);
	
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