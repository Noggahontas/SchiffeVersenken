#pragma once
#include <iostream>
#include "Global_Definitions.h"

using namespace std;

void AttackStrategy3(struct Position* Pos, enum AttackDirection* dir)
{
	// Alle Koordinaten, die mit einem Richtungswechsel zusammenhängen tun machen
	Position S_to_E[5] = { {0,9} , {1,8} , {2,7} , {3,6} , {4,5} };		// Süd Ost Richtungswechsel
	Position E_to_N[5] = { {5,5} , {6,6} , {7,7} , {8,8} , {9,9} };		// Ost Nord Richtungswechsel
	Position N_to_W[5] = { {6,3} , {7,2} , {8,1} , {9,0} };				// Nord West Richtungswechsel
	Position W_to_S[5] = { {1,0} , {2,1} , {3,2} , {4,3} };				// West Süd Richtungswechsel

	// Positionen prüfen (Richtungswechsel):
	for (int ii = 0; ii < 5; ii++)
	{
		if ((Pos->x == S_to_E[ii].x) && (Pos->y == S_to_E[ii].y)) { *dir = E; }
		if ((Pos->x == E_to_N[ii].x) && (Pos->y == E_to_N[ii].y)) { *dir = N; }
		if ((Pos->x == N_to_W[ii].x) && (Pos->y == N_to_W[ii].y)) { *dir = W; }
		if ((Pos->x == W_to_S[ii].x) && (Pos->y == W_to_S[ii].y)) { *dir = S; }
	}
	if ((Pos->x == 5) && (Pos->y == 4)) { Pos->x = 0; Pos->y = 0; return; }


	switch (*dir)
	{
	case S:

		Pos->x = Pos->x;
		Pos->y += 1;
		break;

	case E:

		Pos->x += 1;
		Pos->y = Pos->y;
		break;


	case N:

		Pos->x = Pos->x;
		Pos->y -= 1;
		break;

	case W:

		Pos->x -= 1;
		Pos->y = Pos->y;
		break;
	}
	return;
}