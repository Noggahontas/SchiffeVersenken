#pragma once
#include <iostream>
#include <time.h>						// notwendig für die zeitabhängige Zufallszahl
#include "Global_Definitions.h"

using namespace std;

void AttackStrategy1(struct Position* Position)
{
	Position->x = (rand() % 10);
	Position->y = (rand() % 10);
}