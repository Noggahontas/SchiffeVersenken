#include "stdafx.h"
#include <iostream>
#include "Global_Definitions.h"
#include "AttackStrategy2.h"

using namespace std;
/*
Diagonale Angriffsstrategie, Start bei (0,3). 
Erster Durchlauf: Abstand von 3 Kästchen nach rechts zur nächsten diagonalen Linie.
Zweiter Durchlauf: Abstand nur noch 2 Kästchen zur nächsten Linie.
Dritter Durchlauf: Abstand nur noch 1 Kästchen zur nächsten Linie.


 -	previous_Position: Koordinaten (x,y) im Spiefeld des letzten Angriffs.
 -	new_Positioon: Berechnet die Koordinaten (x,y) für den nächsten Angriff, gibt diese zurück

 -	Strategy_Rounds: 0,1,2 für die Rundenanzahl, wie oft die diagonale Abfolge
	schon durchgeführt wurde.
		0: Erste Runde	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		1: Zweite Runde - 2 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		2: Dritte Runde - 1 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
	Anschliessend wieder von vorne.

*/


Position AttackStrategy2(Position* previous_Position)
{
	static int Strategy_Rounds = 0;
	Position new_Position = { };

	if ((previous_Position->x == NULL) && (previous_Position->y == NULL))
	{
		new_Position.x = 0;
		new_Position.y = 3;
		return new_Position;
	}


	switch (Strategy_Rounds)
	{
	case 0:
		if ((previous_Position->x == 9) || (previous_Position->y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (previous_Position->x == 3)
			{
				new_Position.x = 0;
				new_Position.y = 7;
				return new_Position;
			}
			else if (previous_Position->x == 7)
			{
				new_Position.x = 2;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 2)
			{
				new_Position.x = 6;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 6)
			{
				new_Position.x = 0;
				new_Position.y = 2;
				Strategy_Rounds = 1;
				return new_Position;
			}
		}
		else
		{
			new_Position.x = previous_Position->x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			new_Position.y = previous_Position->y - 1;
			return new_Position;
		}
	case 1:
		if ((previous_Position->x == 9) || (previous_Position->y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (previous_Position->x == 2)
			{
				new_Position.x = 0;
				new_Position.y = 5;
				return new_Position;
			}
			else if (previous_Position->x == 5)
			{
				new_Position.x = 0;
				new_Position.y = 8;
				return new_Position;
			}
			else if (previous_Position->x == 8)
			{
				new_Position.x = 2;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 2)
			{
				new_Position.x = 5;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 5)
			{
				new_Position.x = 8;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 8)
			{
				new_Position.x = 0;
				new_Position.y = 1;
				Strategy_Rounds = 2;
				return new_Position;
			}
		}
		else
		{
			new_Position.x = previous_Position->x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			new_Position.y = previous_Position->y - 1;
			return new_Position;
		}
	case 2:
		if ((previous_Position->x == 9) || (previous_Position->y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (previous_Position->x == 1)
			{
				new_Position.x = 0;
				new_Position.y = 3;
				return new_Position;
			}
			else if (previous_Position->x == 3)
			{
				new_Position.x = 0;
				new_Position.y = 5;
				return new_Position;
			}
			else if (previous_Position->x == 5)
			{
				new_Position.x = 0;
				new_Position.y = 7;
				return new_Position;
			}
			else if (previous_Position->x == 7)
			{
				new_Position.x = 0;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 0)
			{
				new_Position.x = 2;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 2)
			{
				new_Position.x = 4;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 4)
			{
				new_Position.x = 6;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 6)
			{
				new_Position.x = 8;
				new_Position.y = 9;
				return new_Position;
			}
			else if (previous_Position->y == 8)
			{
				new_Position.x = 0;
				new_Position.y = 3;
				Strategy_Rounds = 0;
				return new_Position;
			}
		}
		else
		{
			new_Position.x = previous_Position->x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			new_Position.y = previous_Position->y - 1;
			return new_Position;
		}
	}

	return new_Position;
}


/*

// Test Strat2:
	Position Schuss = {};						// Erste Initialisierung

	int sum = 0;									// Nur zum checken
	for (int ii = 0; ii < 106; ii++)
	{
		Schuss = AttackStrategy2(&Schuss);
		sum = sum + Schuss.x + Schuss.y;
		cout << "(x,y): " << "(" << Schuss.x << "," << Schuss.y << ")" <<
			"\t" << "CheckSum Strat2: " << sum << "/949" << endl;
	}

*/