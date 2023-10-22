
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
	
	double FPS = getFPS();
	
	// ����� ��������� � ������� �������
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
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};