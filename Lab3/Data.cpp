#include "Data.h"

// ������������ ������������ ����
using namespace glm;
using namespace std;

// ������ ����������� ��������
vector<GraphicObject> graphicObjects;

// ������������ ������
Camera camera(10, 15, 17.5);

// �������� �����
Light light(0,10,0);

// ��������
//PhongMaterial material;



GraphicObject obj1;
GraphicObject obj2;
GraphicObject obj3;
GraphicObject obj4;

LARGE_INTEGER previous, frequency;
double interval, fps;
int frameCount = 0;





