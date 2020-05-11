#pragma once
#include <iostream>
#include "Global_Definitions.h"						
using namespace std;
/*
Diagonale Angriffsstrategie, Start bei (0,3), Abstand von 3 Kästchen nach rechts.
-> wird noch angepasst auf Abstände 3-2-1 (in der Reihenfolge)

 - Pos: Koordinaten (x,y) im Spiefeld für den nächsten Angriff.
"Weiss" durch diesen struct auch von der letzten Angriffsposition
und schreibt die neuen Angriffskoordinaten da rein.

*/

void AttackStrategy2(struct Position* Pos)
{
	if ((Pos->x == 9) || (Pos->y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
	{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
		if (Pos->x == 3)
		{
			Pos->x = 0;
			Pos->y = 7;
			return;
		}
		else if (Pos->x == 7)
		{
			Pos->x = 2;
			Pos->y = 9;
			return;
		}
		else if (Pos->y == 2)
		{
			Pos->x = 6;
			Pos->y = 9;
			return;
		}
		else if (Pos->y == 6)
		{
			Pos->x = 0;
			Pos->y = 3;
			return;
		}
	}
	else
	{
		Pos->x = Pos->x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
		Pos->y = Pos->y - 1;
		return;
	}

}


/*
// Test Strat2:
	Position Pos2 = { 0,3 };					// Erster Angriff bei (0,3)
	int sum = 3;									// Nur zum checken
	for (int ii = 0; ii < 23; ii++)
	{
		AttackStrategy2(&Pos2);
		sum = sum + Pos2.x + Pos2.y;
	}
	cout << "(x,y): " << "(" << Pos2.x << "," << Pos2.y << ")" <<
		"\t" <<"CheckSum Strat2: " << sum << "/216"<< endl;
*/