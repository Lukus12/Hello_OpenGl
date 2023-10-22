#pragma once

#include <windows.h>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Data.h"
#include <sstream>

void display(void);
void reshape(int w, int h);