#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "AttackStrategy3.h"

using namespace std;
/*

Spiralförmige Angriffsstrategie, Start bei (0,0), gegen den Uhrzeigersinn,
in den Ecken Richtungswechsel, Ende bei (5,4) und wieder von vorne (0,0).

-	Pos: als static struct -> kein Übergabeparameter mehr
		-	beinhaltet die die Angriffskoordinaten (x,y) des vorherigen Angriffs
			und anschliessend die neu berechneten, die zurückgegeben werden.

 -	AttackDirection: in Norden/Osten/Süden/Westen eingeteilt, 
	für den Richtungswechsel in den Ecken,
	z.B.: bei (x,y) = (0,9) ändert sich AttackDirection von "S" zu "E",
	da es ab diesem Punkt entlang der x-Achse nach "Osten" geht.

*/



Position AttackStrategy3()
{
	static AttackDirection Richtung;

	static Position Pos = { };

	if (((Pos.x == NULL) && (Pos.y == NULL) && (Richtung != AttackDirection::S)))
	{
		Pos.x = 0;
		Pos.y = 0;
		Richtung = AttackDirection::S;
		return Pos;
	}


	// Alle Koordinaten, die mit einem Richtungswechsel zusammenhängen tun machen
	Position S_to_E[5] = { {0,9} , {1,8} , {2,7} , {3,6} , {4,5} };		// Süd-Ost Richtungswechsel
	Position E_to_N[5] = { {5,5} , {6,6} , {7,7} , {8,8} , {9,9} };		// Ost-Nord Richtungswechsel
	Position N_to_W[5] = { {6,3} , {7,2} , {8,1} , {9,0} };				// Nord-West Richtungswechsel
	Position W_to_S[5] = { {1,0} , {2,1} , {3,2} , {4,3} };				// West-Süd Richtungswechsel

	// Positionen prüfen für den Richtungswechsel:
	for (int ii = 0; ii < 5; ii++)
	{
		if ((Pos.x == S_to_E[ii].x) && (Pos.y == S_to_E[ii].y)) { Richtung = AttackDirection::E; break; }
		else if ((Pos.x == E_to_N[ii].x) && (Pos.y == E_to_N[ii].y)) { Richtung = AttackDirection::N; break; }
	}

	for (int ii = 0; ii < 4; ii++)
	{
		if ((Pos.x == N_to_W[ii].x) && (Pos.y == N_to_W[ii].y)) { Richtung = AttackDirection::W; break; }
		else if ((Pos.x == W_to_S[ii].x) && (Pos.y == W_to_S[ii].y)) { Richtung = AttackDirection::S; break; }
	}

	// Am Ende der Spirale angekommen -> zurück zu (0,0)
	if ((Pos.x == 5) && (Pos.y == 4)) { Pos.x = 0; Pos.y = 0; return Pos; }

	// Entsprechend der Angriffsrichtung wird x oder y inkrementiert oder dekrementiert (heißt das so?)

	switch (Richtung)
	{
		case AttackDirection::S:
		{
			Pos.x = Pos.x;
			Pos.y = Pos.y + 1;
			return Pos;
			break;
		}
		case AttackDirection::E:
		{
			Pos.x = Pos.x + 1;
			Pos.y = Pos.y;
			return Pos;
			break;
		}
		case AttackDirection::N:
		{
			Pos.x = Pos.x;
			Pos.y = Pos.y - 1;
			return Pos;
			break;
		}
		case AttackDirection::W:
		{
			Pos.x = Pos.x - 1;
			Pos.y = Pos.y;
			return Pos;
			break;
		}
		default:
		{
			cout << "Selbstzerstörung aktiviert!" << endl;
		}
	}
	return Pos;
}



/*

// Test Strat3:

	Position Schuss = { };
	int sum = 0;
	for (int ii = 0; ii < 100; ii++)
	{
		cout << "(x,y): " << "(" << Schuss.x << "," << Schuss.y << ")" << "\t" << "CheckSum Strat3: " << sum << "/900" << endl;
		Schuss = AttackStrategy3();
		sum = sum + Schuss.x + Schuss.y;

	}

	*/