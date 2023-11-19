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

	frameCount++;

	if (allInterval > 1) {

		averageFPS = frameCount / allInterval;
		allInterval -= 1;

		frameCount = 0;

		oss << "Laba_07 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}

}

void drawField() {
	// выбираем активный текстурный блок
	glActiveTexture(GL_TEXTURE0);
	// разрешаем текстурирование в выбранном элементе текстурного блока
	glEnable(GL_TEXTURE_2D);
	// привязываем текстуру к ранее выбранному текстурному блоку
	planeTexture.apply();
	// указываем режим наложения текстуры (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// выводим плоскость
	field.draw();
	// отключаем текстурирование (чтобы все остальные объекты выводились без текстур)
	Texture::disableAll();
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

	drawField();
	
	if (player != nullptr) (*player).draw();

	for (int i = 0; i < 5; i++) {
		if (monsters[i] != nullptr) (*monsters[i]).draw();
	}

	if (bomb != nullptr) {
		(*bomb).draw();
	}


	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			if (mapObjects[i][j] != nullptr) (*mapObjects[i][j]).draw();
		}
	}

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

