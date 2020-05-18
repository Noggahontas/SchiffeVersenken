#include "stdafx.h"
#include <iostream>
#include <time.h>						// notwendig für die zeitabhängige Zufallszahl
#include "Global_Definitions.h"
#include "AttackStrategy1.h"

using namespace std;


/*

 - new_Position: neue Koordinaten (x,y) im Spielfeld, auf die der nächste Angriff erfolgt

*/


Position AttackStrategy1()
{
	Position new_Position = { 0 , 0 };

	new_Position.x = (rand() % 10);					// erzeugen einer Zufallszahl zwischen 0 und 9 für x und y
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
