#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "AttackStrategy3.h"

using namespace std;
/*

Spiralförmige Angriffsstrategie, Start bei (0,0), gegen den Uhrzeigersinn,
in den Ecken Richtungswechsel, Ende bei (5,4) und wieder von vorne (0,0).

 -	previous_Position: Koordinaten (x,y) im Spielfeld des letzten Angriffs.

 -	new_Position: berechnete Koordinaten (x,y) für den nächsten Angriff

 -	AttackDirection: in Norden/Osten/Süden/Westen eingeteilt, 
	für den Richtungswechsel in den Ecken,
	z.B.: bei (x,y) = (0,9) ändert sich AttackDirection von "S" zu "E",
	da es ab diesem Punkt entlang der x-Achse nach "Osten" geht.
	Vermutlich hätte da einach nur ein int 0,1,2,3 gereicht.

*/



Position AttackStrategy3(Position *previous_Position)
{
	static AttackDirection Richtung;

	Position new_Position = {};

	if (((previous_Position->x == NULL) && (previous_Position->y == NULL) && (Richtung != AttackDirection::S)))
	{
		new_Position.x = 0;
		new_Position.y = 0;
		Richtung = AttackDirection::S;
		return new_Position;
	}


	// Alle Koordinaten, die mit einem Richtungswechsel zusammenhängen tun machen
	Position S_to_E[5] = { {0,9} , {1,8} , {2,7} , {3,6} , {4,5} };		// Süd-Ost Richtungswechsel
	Position E_to_N[5] = { {5,5} , {6,6} , {7,7} , {8,8} , {9,9} };		// Ost-Nord Richtungswechsel
	Position N_to_W[5] = { {6,3} , {7,2} , {8,1} , {9,0} };				// Nord-West Richtungswechsel
	Position W_to_S[5] = { {1,0} , {2,1} , {3,2} , {4,3} };				// West-Süd Richtungswechsel

	// Positionen prüfen für den Richtungswechsel:
	for (int ii = 0; ii < 5; ii++)
	{
		if ((previous_Position->x == S_to_E[ii].x) && (previous_Position->y == S_to_E[ii].y)) { Richtung = AttackDirection::E; break; }
		else if ((previous_Position->x == E_to_N[ii].x) && (previous_Position->y == E_to_N[ii].y)) { Richtung = AttackDirection::N; break; }
	}

	for (int ii = 0; ii < 4; ii++)
	{
		if ((previous_Position->x == N_to_W[ii].x) && (previous_Position->y == N_to_W[ii].y)) { Richtung = AttackDirection::W; break; }
		else if ((previous_Position->x == W_to_S[ii].x) && (previous_Position->y == W_to_S[ii].y)) { Richtung = AttackDirection::S; break; }
	}

	// Am Ende der Spirale angekommen -> zurück zu (0,0)
	if ((previous_Position->x == 5) && (previous_Position->y == 4)) { new_Position.x = 0; new_Position.y = 0; return new_Position; }

	// Entsprechend der Angriffsrichtung wird x oder y inkrementiert oder dekrementiert (heißt das so?)

	switch (Richtung)
	{
		case AttackDirection::S:
		{
			new_Position.x = previous_Position->x;
			new_Position.y = previous_Position->y + 1;
			return new_Position;
			break;
		}
		case AttackDirection::E:
		{
			new_Position.x = previous_Position->x + 1;
			new_Position.y = previous_Position->y;
			return new_Position;
			break;
		}
		case AttackDirection::N:
		{
			new_Position.x = previous_Position->x;
			new_Position.y = previous_Position->y - 1;
			return new_Position;
			break;
		}
		case AttackDirection::W:
		{
			new_Position.x = previous_Position->x - 1;
			new_Position.y = previous_Position->y;
			return new_Position;
			break;
		}
		default:
		{
			cout << "Selbstzerstörung aktiviert!" << endl;
		}
	}
	return new_Position;
}



/*

// Test Strat3:

	Position Schuss = { };
	int sum = 0;
	for (int ii = 0; ii < 100; ii++)
	{
		cout << "(x,y): " << "(" << Schuss.x << "," << Schuss.y << ")" << "\t" << "CheckSum Strat3: " << sum << "/900" << endl;
		Schuss = AttackStrategy3(&Schuss);
		sum = sum + Schuss.x + Schuss.y;

	}

	*/