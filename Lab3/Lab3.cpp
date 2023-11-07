#include <windows.h>

#include "GL/glew.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

#include "rapidjson/document.h"

#include "Scene\Camera\Camera.h"
#include "Display\Display.h"
#include "Display\Simulation.h"
#include "Data\Data.h"




// используем пространство имен стандартной библиотеки
using namespace std;
using namespace glm;


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
	glutSetWindowTitle("Laba_07 [ ]");
	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previous);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	// инициализация GLEW
	GLenum err = glewInit();
	

	initData();

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


