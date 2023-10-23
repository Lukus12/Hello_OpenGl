
#include "Display.h"


extern LARGE_INTEGER previous, frequency;

int frameCount = 0;
double interval, fps; 
double allFPS = 0;
double averageFPS = 0;
//������� ���������� fps ����� �� ����� � �������� �� �� ���-�� ������ 1000 ��������(����� ����������)

double allInterval=0;

void winFPS() {
	std::ostringstream oss;
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	interval = static_cast<double>(current.QuadPart - previous.QuadPart) / frequency.QuadPart;
	allInterval += interval;

	previous = current;

	fps = 1.0 / interval;
	allFPS += fps;

	frameCount++;

	if (allInterval > 1) {

		allInterval -= 1;

		averageFPS = allFPS / frameCount;

		frameCount = 0;
		allFPS = 0;

		oss << "Laba_04 [" << averageFPS << " FPS]";
		glutSetWindowTitle(oss.str().c_str());
	}


}

void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	// �������� ����� ������� ���������
	glEnable(GL_LIGHTING);
	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.apply();
	light.apply(GL_LIGHT0);
	// ������� ��� ����������� �������
	for (auto& go : graphicObjects) {
		go.draw();
	}
	
	winFPS();
	
	// ����� ��������� � ������� �������
	glutSwapBuffers();

};

void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};