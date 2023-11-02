
#include "Display.h"



extern LARGE_INTEGER previous, frequency;

int frameCount = 0;
double interval, fps; 
//double allFPS = 0;
double averageFPS = 0;
//считать результаты fps через их сумму и поделить на их кол-во спустя 1000 миллисек(сумма интервалов)

double allInterval=0;

void winFPS() {
	std::ostringstream oss;
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	interval = static_cast<double>(current.QuadPart - previous.QuadPart) / frequency.QuadPart;
	allInterval += interval;

	previous = current;

	//fps = 1.0 / interval;
	//allFPS += fps;

	frameCount++;

	if (allInterval > 1) {


		//averageFPS = allFPS / frameCount;
		averageFPS = frameCount / allInterval;
		allInterval -= 1;

		frameCount = 0;
		//allFPS = 0;

		oss << "Laba_06 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}


}

void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// включаем режим расчета освещения
	glEnable(GL_LIGHTING);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.apply();
	light1.apply(GL_LIGHT0);
	//light2.apply(GL_LIGHT0); // x 25 сзади
	//light3.apply(GL_LIGHT0); // z 25 слева
	//light4.apply(GL_LIGHT1); // x -25 спереди
	//light5.apply(GL_LIGHT0); // z -25 справа
		// выводим все графические объекты
	for (auto& go : graphicObjects) {
		go->draw();
	}


	/*for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}*/

	winFPS();
	
	// смена переднего и заднего буферов
	glutSwapBuffers();

};

void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};