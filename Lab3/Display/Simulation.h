#pragma once

#include <iostream>

#include "GL/glew.h"

#include "..\Data\Data.h"


void simulation();
void moveCamera(float simulationTime);
double getSimulationTime();