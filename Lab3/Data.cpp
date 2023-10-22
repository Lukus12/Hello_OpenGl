#include "Data.h"

// используемые пространства имен
using namespace glm;
using namespace std;

// список графических объектов
vector<GraphicObject> graphicObjects;

// используемая камера
Camera camera(10, 15, 17.5);

// источник света
Light light(0,10,0);

// материал
//PhongMaterial material;



GraphicObject obj1;
GraphicObject obj2;
GraphicObject obj3;
GraphicObject obj4;

LARGE_INTEGER previous, frequency;
double interval, fps;
int frameCount = 0;





