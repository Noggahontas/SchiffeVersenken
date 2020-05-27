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


 -	Pos: als static struct -> kein Übergabeparameter mehr
	-	beinhaltet die die Angriffskoordinaten (x,y) des vorherigen Angriffs
		und anschliessend die neu berechneten, die zurückgegeben werden.

 -	Strategy_Rounds: 0,1,2 für die Rundenanzahl, wie oft die diagonale Abfolge
	schon durchgeführt wurde.
		0: Erste Runde	- Start {0,3}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		1: Zweite Runde	- Start {0,2}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		2: Dritte Runde - Start {0,1}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		3: Vierte Runde - Start {0,4}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
	Anschliessend wieder von vorne.

*/


Position AttackStrategy2()
{
	static int Strategy_Rounds = 0;

	static Position Pos = { };

	if ((Pos.x == NULL) && (Pos.y == NULL))
	{
		Pos.x = 0;
		Pos.y = 3;
		return Pos;
	}

	switch (Strategy_Rounds)
	{
	case 0:
		if ((Pos.x == 9) || (Pos.y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{																			// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (Pos.x == 3)
			{
				Pos = { 0,7 };
				return Pos;
			}
			else if (Pos.x == 7)
			{
				Pos = { 2,9 };
				return Pos;
			}
			else if (Pos.y == 2)
			{
				Pos = { 6,9 };
				return Pos;
			}
			else if (Pos.y == 6)
			{
				Pos = { 0,2 };
				Strategy_Rounds = 1;
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			Pos.y = Pos.y - 1;
			return Pos;
		}
	case 1:
		if ((Pos.x == 9) || (Pos.y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (Pos.x == 2)
			{
				Pos = { 0,6 };
				return Pos;
			}
			else if (Pos.x == 6)
			{
				Pos = { 1,9 };
				return Pos;
			}
			else if (Pos.y == 1)
			{
				Pos = { 5,9 };
				return Pos;
			}
			else if (Pos.y == 5)
			{
				Pos = { 9,9 };
				return Pos;
			}
			else if (Pos.y == 9)
			{
				Pos = { 0,1 };
				Strategy_Rounds = 2;
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			Pos.y = Pos.y - 1;
			return Pos;
		}
	case 2:
		if ((Pos.x == 9) || (Pos.y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (Pos.x == 1)
			{
				Pos = { 0,5 };
				return Pos;
			}
			else if (Pos.x == 5)
			{
				Pos = { 0,9 };
				return Pos;
			}
			else if (Pos.y == 0)
			{
				Pos = { 4,9 };
				return Pos;
			}
			else if (Pos.y == 4)
			{
				Pos = { 8,9 };
				return Pos;
			}
			else if (Pos.y == 8)
			{
				Pos.x = 0;
				Pos.y = 4;
				Strategy_Rounds = 3;
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			Pos.y = Pos.y - 1;
			return Pos;
		}
	case 3:
		if ((Pos.x == 9) || (Pos.y == 0))				// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{												// da dort das Spielfeld verlassen und von neuem Punkt aus gestartet wird.
			if (Pos.x == 4)
			{
				Pos = { 0,8 };
				return Pos;
			}
			else if (Pos.x == 5)
			{
				Pos = { 0,9 };
				return Pos;
			}
			else if (Pos.x == 8)
			{
				Pos = { 3,9 };
				return Pos;
			}
			else if (Pos.y == 3)
			{
				Pos = { 7,9 };
				return Pos;
			}
			else if (Pos.y == 7)
			{
				Pos.x = 0;
				Pos.y = 0;
				Strategy_Rounds = 0;
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;					// Angriffsrichtung läuft diagonal rechts hoch - Richtung bleibt konstant
			Pos.y = Pos.y - 1;
			return Pos;
		}
	}

	return Pos;
}


/*

// Test Strat2:
	Position Schuss = {};						// Erste Initialisierung

	int sum = 0;									// Nur zum checken
	for (int ii = 0; ii < 100; ii++)
	{
		Schuss = AttackStrategy2();
		sum = sum + Schuss.x + Schuss.y;
		cout << "(x,y): " << "(" << Schuss.x << "," << Schuss.y << ")" <<
			"\t" << "CheckSum Strat2: " << sum << "/900" << endl;
	}


*/