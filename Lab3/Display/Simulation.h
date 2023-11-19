#pragma once

#include <iostream>

#include "..\Data\Data.h"

extern GameObjectFactory gameObjectFactory;

void movePlayer();
void gameObjectSimulation(float simulationTime);
void simulation();
void moveCamera(float simulationTime);
double getSimulationTime();