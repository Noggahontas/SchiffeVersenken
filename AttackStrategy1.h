#pragma once

#include <iostream>
#include <time.h>						// notwendig f�r die zeitabh�ngige Zufallszahl 

using namespace std;

void Angriffsstrategie1(int* x, int* y)
{
	*x = (rand() % 10) + 1;
	*y = (rand() % 10) + 1;
}