#include "stdafx.h"
#include <iostream>
#include <time.h>						// notwendig f�r die zeitabh�ngige Zufallszahl
#include "Global_Definitions.h"
#include "AttackStrategy1.h"

using namespace std;


/*
Angriffsstrategie1:
Strategie gibt beim Aufruf f�r den x- und f�r den y-Wert jeweils eine Zufallszahl zwischen 0 und 9 zur�ck

 - new_Position: struct f�r die neuen Koordinaten (x,y) im Spielfeld, auf die der n�chste Angriff erfolgt

*/


Position AttackStrategy1()
{
	Position new_Position = { };

	new_Position.x = (rand() % 10);					// erzeugen einer Zufallszahl zwischen 0 und 9 f�r x und y
	new_Position.y = (rand() % 10);

	return new_Position;
}




/*

// Test Strat1:
	Position Schuss;								// da stehen die Angriffskoordinaten

	for (int ii = 0; ii < 10; ii++)
	{
		Schuss = AttackStrategy1();					// Angriffskoordinaten holen
		cout << "Strat 1: Coordinates to be attacked (x,y): " <<
			"(" << (Schuss.x) << "," << (Schuss.y) << ")" << "  " << "Pew Pew" << endl;
	}
*/
