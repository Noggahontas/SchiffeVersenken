#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "AttackStrategy3.h"

using namespace std;
/*
Angriffsstrategie 3:

Spiralförmige Angriffsstrategie, Start bei (0,0), gegen den Uhrzeigersinn,
in den Ecken Richtungswechsel, Ende bei (5,4) und wieder von vorne (0,0).

 -	Position Pos: als static struct - beinhaltet die Angriffskoordinaten (x,y) des vorherigen Angriffs
	und anschliessend die neu berechneten, die zurückgegeben werden.

 -	AttackDirection: in Norden/Osten/Süden/Westen eingeteilt, 
	für den Richtungswechsel in den Eckpunkten.

	z.B.: bei (x,y) = (0,9) ändert sich AttackDirection von "S" zu "E",
	da es ab diesem Punkt entlang der x-Achse nach "Osten" geht.


*/



Position AttackStrategy3()
{
	static AttackDirection Richtung;	// Für die Richtung, in die geschossen werden soll
	static bool Direction = false;		// notwendig zum unterscheiden zwischen Situation {NULL,NULL} und {0,0}

	static Position Pos = { };			// beinhaltet die vorherige und dann die neu berechneten Koordinaten

	// Der erste Schuss von jedem Durchlauf startet bei {0,0} und hat als Richtung "Süden" ausgewählt
	if (((Pos.x == NULL) && (Pos.y == NULL) && (Direction == false)) || ((Pos.x == 5) && (Pos.y == 4)))
	{
		Pos.x = 0;
		Pos.y = 0;
		Richtung = AttackDirection::S;
		Direction = true;
		return Pos;
	}


	// Alle Koordinaten, die mit einem Richtungswechsel zusammenhängen (jeweils die Eckpunkte)
	Position S_to_E[5] = { {0,9} , {1,8} , {2,7} , {3,6} , {4,5} };		// Süd-Ost Richtungswechsel
	Position E_to_N[5] = { {5,5} , {6,6} , {7,7} , {8,8} , {9,9} };		// Ost-Nord Richtungswechsel
	Position N_to_W[5] = { {6,3} , {7,2} , {8,1} , {9,0} };				// Nord-West Richtungswechsel
	Position W_to_S[5] = { {1,0} , {2,1} , {3,2} , {4,3} };				// West-Süd Richtungswechsel

	// letzter Schuss mit den Eckpunkt-Koordinaten vergleichen, falls erreicht -> Richtungswechsel
	// Richtungswechsel von Süden nach Osten oder von Osten zu Norden prüfen
	for (int ii = 0; ii < 5; ii++)
	{
		if ((Pos.x == S_to_E[ii].x) && (Pos.y == S_to_E[ii].y)) { Richtung = AttackDirection::E; break; }
		else if ((Pos.x == E_to_N[ii].x) && (Pos.y == E_to_N[ii].y)) { Richtung = AttackDirection::N; break; }
	}
	// Richtungswechsel von Norden nach Westen oder von Westen nach Süden prüfen
	for (int ii = 0; ii < 4; ii++)
	{
		if ((Pos.x == N_to_W[ii].x) && (Pos.y == N_to_W[ii].y)) { Richtung = AttackDirection::W; break; }
		else if ((Pos.x == W_to_S[ii].x) && (Pos.y == W_to_S[ii].y)) { Richtung = AttackDirection::S; break; }
	}


	// Abhängig von der Angriffsrichtung werden neue Koordinaten berechnet
	switch (Richtung)
	{
		case AttackDirection::S:					// Angriffsrichtung ist Süden (z.B. die erste Spalte bei x=0)
		{
			Pos.x = Pos.x;							// x-Wert bleibt gleich
			Pos.y = Pos.y + 1;						// y-Wert wird inkrementiert
			return Pos;
			break;
		}
		case AttackDirection::E:					// Angriffsrichtung ist Osten (z.B. die letzte Zeile bei y=9)
		{
			Pos.x = Pos.x + 1;						
			Pos.y = Pos.y;							
			return Pos;
			break;
		}
		case AttackDirection::N:					// Angriffsrichtung ist Norden (z.B. die letzte Spalte bei x=9)
		{
			Pos.x = Pos.x;							
			Pos.y = Pos.y - 1;						
			return Pos;
			break;
		}
		case AttackDirection::W:					// Angriffsrichtung ist Westen (z.B. die erste Zeile bei y=0)
		{
			Pos.x = Pos.x - 1;						
			Pos.y = Pos.y;							
			return Pos;
			break;
		}
		default:
		{
			cout << "AttackStrategy2: Da stimmt was nicht!" << endl;
		}
	}
	return Pos;
}



/*

// Test Strat3:

	Position Schuss = { };
	int sum = 0;
	for (int ii = 0; ii < 200; ii++)
	{
		Schuss = AttackStrategy3();
		sum = sum + Schuss.x + Schuss.y;
		cout << "(x,y): " << "(" << Schuss.x << "," << Schuss.y << ")" << "\t" << "CheckSum Strat3: " << sum << "/900" << endl;
	}

	*/