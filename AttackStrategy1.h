#pragma once

#include <iostream>
#include <time.h>						// notwendig für die zeitabhängige Zufallszahl 

using namespace std;

void Angriffsstrategie1(int* x, int* y)
{
	*x = (rand() % 10) + 1;
	*y = (rand() % 10) + 1;
}