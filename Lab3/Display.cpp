
#include "Display.h"


extern LARGE_INTEGER previous, frequency;
extern double interval, fps;
extern int frameCount;


double getFPS() {
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);
	interval = static_cast<double>(current.QuadPart - previous.QuadPart) / frequency.QuadPart;
	previous = current;

	fps = 1.0 / interval;

	return fps;
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
	light.apply(GL_LIGHT0);
	// выводим все графические объекты
	for (auto& go : graphicObjects) {
		go.draw();
	}
	
	double FPS = getFPS();
	
	// смена переднего и заднего буферов
	glutSwapBuffers();
	
	frameCount++;
	std::ostringstream oss;
	if (frameCount % 2000 == 0) {
		oss << "Laba_04 [" << FPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
		frameCount = 0;
	}

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