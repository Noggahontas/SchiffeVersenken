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
		0: Erste Runde	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		1: Zweite Runde - 2 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		2: Dritte Runde - 1 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
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
				Pos.x = 0;
				Pos.y = 7;
				return Pos;
			}
			else if (Pos.x == 7)
			{
				Pos.x = 2;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 2)
			{
				Pos.x = 6;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 6)
			{
				Pos.x = 0;
				Pos.y = 2;
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
				Pos.x = 0;
				Pos.y = 5;
				return Pos;
			}
			else if (Pos.x == 5)
			{
				Pos.x = 0;
				Pos.y = 8;
				return Pos;
			}
			else if (Pos.x == 8)
			{
				Pos.x = 2;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 2)
			{
				Pos.x = 5;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 5)
			{
				Pos.x = 8;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 8)
			{
				Pos.x = 0;
				Pos.y = 1;
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
				Pos.x = 0;
				Pos.y = 3;
				return Pos;
			}
			else if (Pos.x == 3)
			{
				Pos.x = 0;
				Pos.y = 5;
				return Pos;
			}
			else if (Pos.x == 5)
			{
				Pos.x = 0;
				Pos.y = 7;
				return Pos;
			}
			else if (Pos.x == 7)
			{
				Pos.x = 0;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 0)
			{
				Pos.x = 2;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 2)
			{
				Pos.x = 4;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 4)
			{
				Pos.x = 6;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 6)
			{
				Pos.x = 8;
				Pos.y = 9;
				return Pos;
			}
			else if (Pos.y == 8)
			{
				Pos.x = 0;
				Pos.y = 3;
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
	for (int ii = 0; ii < 106; ii++)
	{
		Schuss = AttackStrategy2();
		sum = sum + Schuss.x + Schuss.y;
		cout << "(x,y): " << "(" << Schuss.x << "," << Schuss.y << ")" <<
			"\t" << "CheckSum Strat2: " << sum << "/949" << endl;
	}


*/