#pragma once
#include <iostream>
#include <time.h>						// notwendig f�r die zeitabh�ngige Zufallszahl
#include "Global_Definitions.h"

using namespace std;

void AttackStrategy1(struct Position* Position)
{
	Position->x = (rand() % 10);
	Position->y = (rand() % 10);
}