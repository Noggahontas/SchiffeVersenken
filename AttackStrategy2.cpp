#include "stdafx.h"
#include <iostream>
#include "Global_Definitions.h"
#include "AttackStrategy2.h"

using namespace std;
/*
Angriffsstrategie 2:
Vier Durchläufe in diagonalen Linien vom linken Rand zum oberen Rand, bzw vom unteren Rand zum rechten Rand 

 -	Position Pos: als static struct - beinhaltet die Angriffskoordinaten (x,y) des vorherigen Angriffs
		und anschliessend die neu berechneten, die zurückgegeben werden.

 -	Strategy_Rounds: 0, 1, 2, 3 für die Anzahl der Durchläufe.
		0: Erste Runde	- Start {0,3}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		1: Zweite Runde	- Start {0,2}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		2: Dritte Runde - Start {0,1}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
		3: Vierte Runde - Start {0,4}	- 3 Kästchen Abstand in x-Richtung zur nächsten diagonalen Linie
	Anschliessend wieder von vorne.

	Reihe y=0 bzw. Spalte x=9 sind die Bereiche, in denen eine diagonale Linie abbricht 
	um anschliessend eine neue diagonale Linie zu starten in der Spalte x=0 bzw. Reihe y=9
*/


//Position AttackStrategy2()
//{
//	static int Strategy_Rounds = 0;					// Enthält die Nummer des aktuellen Durchlaufes
//
//	static Position Pos = { };						// beinhaltet die vorherigen Angriffskoordinaten 
//													// und für die Rückgabe die neu bestimmen Koordinaten
//
//	if ((Pos.x == NULL) && (Pos.y == NULL))			// Am Ende des letzten Durchlaufs muss von {0,0} zu {0,3} gewechselt werden
//	{
//		Pos.x = 0;
//		Pos.y = 3;
//		return Pos;
//	}
//
//	switch (Strategy_Rounds)						// Jeder Durchlauf hat unterschiedliche Start-/Endpunkte
//	{
//	case 0:											// Erster Durchlauf
//		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
//		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
//			if (Pos.x == 3)							// Endpunkt der ersten diagonalen Linie bei {3,0} -> return neuer Startpunkt 
//			{
//				Pos = { 0,7 };						// Startpunkt der neuen diagonalen Linie
//				return Pos;
//			}
//			else if (Pos.x == 7)					// Endpunkt der zweiten diagonalen Linie bei {0,7} -> return neuer Startpunkt
//			{
//				Pos = { 2,9 };						// Startpunkt der neuen diagonalen Linie
//				return Pos;
//			}
//			else if (Pos.y == 2)					// Endpunkt der dritten diagonalen Linie bei {9,2} -> return neuer Startpunkt
//			{
//				Pos = { 6,9 };						// Startpunkt der neuen diagonalen Linie
//				return Pos;
//			}
//			else if (Pos.y == 6)					// Endpunkt der vierten diagonalen Linie bei {9,6} -> return neuer Startpunkt
//			{
//				Pos = { 0,2 };						// Startpunkt der neuen diagonalen Linie
//				Strategy_Rounds = 1;				// Zweiter Durchlauf beim nächsten Aufruf
//				return Pos;
//			}
//		}
//		else
//		{
//			Pos.x = Pos.x + 1;						// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
//			Pos.y = Pos.y - 1;						
//			return Pos;
//		}
//	case 1:
//		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
//		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
//			if (Pos.x == 2)							// Endpunkt der ersten diagonalen Linie {0,9} -> return neuer Startpunkt
//			{
//				Pos = { 0,6 };						// Startpunkt der neuen diagonalen Linie
//				return Pos;
//			}
//			else if (Pos.x == 6)
//			{
//				Pos = { 1,9 };
//				return Pos;
//			}
//			else if (Pos.y == 1)
//			{
//				Pos = { 5,9 };
//				return Pos;
//			}
//			else if (Pos.y == 5)
//			{
//				Pos = { 9,9 };
//				return Pos;
//			}
//			else if (Pos.y == 9)
//			{
//				Pos = { 0,1 };
//				Strategy_Rounds = 2;				// Dritter Durchlauf beim nächsten Aufruf
//				return Pos;
//			}
//		}
//		else
//		{
//			Pos.x = Pos.x + 1;						// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
//			Pos.y = Pos.y - 1;
//			return Pos;
//		}
//	case 2:
//		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
//		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
//			if (Pos.x == 1)
//			{
//				Pos = { 0,5 };
//				return Pos;
//			}
//			else if (Pos.x == 5)
//			{
//				Pos = { 0,9 };
//				return Pos;
//			}
//			else if (Pos.y == 0)
//			{
//				Pos = { 4,9 };
//				return Pos;
//			}
//			else if (Pos.y == 4)
//			{
//				Pos = { 8,9 };
//				return Pos;
//			}
//			else if (Pos.y == 8)
//			{
//				Pos.x = 0;
//				Pos.y = 4;
//				Strategy_Rounds = 3;				// vierter Durchlauf beim nächsten Aufruf
//				return Pos;
//			}
//		}
//		else
//		{
//			Pos.x = Pos.x + 1;						// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
//			Pos.y = Pos.y - 1;
//			return Pos;
//		}
//	case 3:
//		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
//		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
//			if (Pos.x == 4)
//			{
//				Pos = { 0,8 };
//				return Pos;
//			}
//			else if (Pos.x == 5)
//			{
//				Pos = { 0,9 };
//				return Pos;
//			}
//			else if (Pos.x == 8)
//			{
//				Pos = { 3,9 };
//				return Pos;
//			}
//			else if (Pos.y == 3)
//			{
//				Pos = { 7,9 };
//				return Pos;
//			}
//			else if (Pos.y == 7)
//			{
//				Pos.x = 0;
//				Pos.y = 0;
//				Strategy_Rounds = 0;			// Am Ende des vierten Durchlaufs wird wieder mit dem ersten Durchlauf
//				return Pos;						// im nächsten Aufruf gestartet
//			}
//		}
//		else
//		{
//			Pos.x = Pos.x + 1;					// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
//			Pos.y = Pos.y - 1;
//			return Pos;
//		}
//	}
//
//	return Pos;
//}


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