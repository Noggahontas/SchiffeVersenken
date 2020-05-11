#pragma once
#include <iostream>
#include <time.h>						// notwendig f�r die zeitabh�ngige Zufallszahl
#include "Global_Definitions.h"

using namespace std;

/*

 - Pos: Koordinaten (x,y) im Spielfeld, f�r die n�chsten Angriffskoordinaten

*/


void AttackStrategy1(struct Position* Position)		
{
	Position->x = (rand() % 10);					// erzeugen einer Zufallszahl zwischen 0 und 9 f�r x und y
	Position->y = (rand() % 10);
}




/*
// Test Strat1:
Position Pos1;							// da stehen die Angriffskoordinaten
AttackStrategy1(&Pos1);							// Angriffskoordinaten holen
cout << endl << "Strat 1: Coordinates to be attacked (x,y): " <<
"(" << (Pos1.x) << "," << (Pos1.y) << ")" << "  " << "Pew Pew" << endl;
*/