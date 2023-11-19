#include "Display.h"

extern LARGE_INTEGER previous, frequency;

int frameCount = 0;
double interval, fps; 
//double allFPS = 0;
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
	// �������� �������� ���������� ����
	glActiveTexture(GL_TEXTURE0);
	// ��������� ��������������� � ��������� �������� ����������� �����
	glEnable(GL_TEXTURE_2D);
	// ����������� �������� � ����� ���������� ����������� �����
	planeTexture.apply();
	// ��������� ����� ��������� �������� (GL_MODULATE)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// ������� ���������
	field.draw();
	// ��������� ��������������� (����� ��� ��������� ������� ���������� ��� �������)
	Texture::disableAll();
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

