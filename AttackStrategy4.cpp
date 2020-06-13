#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "AttackStrategy4.h"
#include <time.h>

using namespace std;

/*
-----------------------------------------------------------------------------------------------------------------------
Angriffsstrategie 4:

	- Strategie wählt zufällige Punkte, falls kein Schiff gesucht wird
		
		Bei einem Treffer der Zufallskoordinaten wird zuerst die Ausrichtung des Schiffes gesucht 
		(heißt einfach die Schussrichtung in einer bestimmten Reihenfolge abgearbeitet):
			Schuss nördlich von den Startkoordinaten,
				wenn hit, wieder nördlicher Schuss -> bis miss oder Feldrand
				wenn miss oder Feldrand, südlich der Startkoordinaten
					wenn hit, wieder südlicher Schuss -> bis miss oder Feldrand
					wenn miss oder Feldrand, östlich der Startkoordinaten
						wenn hit, wieder östlicher Schuss -> bis miss oder Feldrand
						wenn miss oder Feldrand, westlich der Startkoordinaten
							wenn hit, wieder westlicher Schuss -> bis miss oder Feldrand
							wenn miss oder Feldrand, neue Zufallskoordinaten und von vorne starten (Norden -> Süden -> Osten -> Westen)
		Wird zwischendurch ein Schiff versenkt, beginnt die Strategie von vorn mit Zufallskoordinaten.

		Strategie benötigt als Übergabeparameter die Information, ob der letzte eigene Schuss ein Treffer war (LastShotHit)
		und ob das grade beschossene Schiff versenkt wurde (sunk).
		

*/

// Ausgelagerte "Berechnung" der nächsten Koordinaten:

// Schüsse nach Norden ändern den x-Wert nicht, der y-Wert wird dekrementiert: x=x und y=y-1
Position ShootNorth(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x;
	new_Pos.y = previous_Position->y - 1;
	return new_Pos;
}

// Schüsse nach Süden ändern den x-Wert nicht, der y-Wert wird inkrementiert: x=x und y=y+1
Position ShootSouth(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x;
	new_Pos.y = previous_Position->y + 1;
	return new_Pos;
}

// Schüsse nach Osten ändern den y-Wert nicht, der x-Wert wird inkrementiert: y=y und x=x+1
Position ShootEast(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x + 1;
	new_Pos.y = previous_Position->y;
	return new_Pos;
}
// Schüsse nach Westen ändern den y-Wert nicht, der x-Wert wird dekrementiert: y=y und x=x-1
Position ShootWest(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x - 1;
	new_Pos.y = previous_Position->y;
	return new_Pos;
}

// Berechnung neuer Zufallskoordinaten (x-,y-Werte zwischen 0 und 9):
Position rndCoordinates()
{
	Position new_pos = {};
	new_pos.x = (rand() % 10);
	new_pos.y = (rand() % 10);
	return new_pos;
}


Position AttackStrategy4(bool *LastShotHit, bool *sunk)
{
	static Position Pos = { };					// Beinhaltet die Koordinaten des vorherigen Schusses bzw nach der Berechnung die neuen Angriffskoordinaten
	static bool alreadyShot = false;			// Wenn schonmal geschossen wurde (true) -> für bestimmte Abfragen

	static AttackDirection Direction;			// zeigt die Angriffsrichtung an für den nächsten
	static bool DirectionChoice = false;		// zur Unterscheidung zwischen neuen rnd-Koordinaten und Richtungswechselabfrage

	static bool FieldBorder = false;			// Kollision mit dem Spielfeldrand muss gesondert behandelt werden
	
	static Position first_hit = {};				// merken des ersten Schusses (die ersten rnd-Koordinaten bei jeder Suchfolge)
	
	
	// Erster Schuss (Bedingungen: x und y = NULL) -> rnd-Koordinaten zurückgeben
	// ODER
	// Ging vorherige Schuss daneben UND es wurde schon geschossen UND Richtung noch nicht gewählt -> neue rnd-Koordinaten zurückgeben
	// ODER
	// Der vorherhige Schuss hat ein Schiff versenkt -> neue rnd-Koordinaten zurückgeben
	if (((Pos.x == NULL) && (Pos.y == NULL)) || ((*LastShotHit == false) && (alreadyShot == true) && (!DirectionChoice)) || (*sunk == true))
	{
		if (*sunk == true)							// Falls das angegriffene Schiff des vorherigen Schusses versenkt wirde
		{											// werden bestimmte Hilfsvariablen zurückgesetzt
			DirectionChoice = false;
		}
		Direction = AttackDirection::N;				// erste Angriffsrichtung ist immer Norden
		Pos = rndCoordinates();						// Zufallskoordinaten generieren
		alreadyShot = true;							// Hilfsvariable setzen
		first_hit = Pos;							// Zufalskoordinaten werden in first_hit geschrieben -> wird beim Richtungswechsel benötigt
		return Pos;									// neue Angriffskoordinaten zurückgeben
	}

	// Waren Zufallskoordinaten ein Treffer UND es wurde auch geschossen UND die Angriffsrichtung wurde gewählt,
	// dann kann die "Schiffsuche" starten (zuerst Richtung Norden)
	if ((*LastShotHit == true) && (alreadyShot == true) && (!DirectionChoice))
	{
		Direction = AttackDirection::N;
		DirectionChoice = true;
	}


	
	// Wenn der letzte Schuss nicht getroffen hat, aber geschossen wurde, muss die Richtung gewechselt werden, 
	// abhängig von der aktuell aktiven Richtung. 
	// (Wenn z.B. beim schießen in Richtung Süden ein Schuss daneben geht, 
	// muss die Richtung nach Osten gewechselt werden.)
	if (((*LastShotHit == false) && (alreadyShot)))
	{	// Wenn die Angriffsrichtung bisher Norden war oder die nächsten Koordinaten ausserhalb des nördlichen Randes (y<0) landen,
		// muss die Richtung nach Süden wechseln
		if ((Direction == AttackDirection::N) || ((Direction == AttackDirection::N) && ((Pos.y - 1) < 0)))	
		{	
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true) 
			{													// (wird hier vermutlich nicht nötig sein, da vor Norden nur Zufallswahl kommt) 
				FieldBorder = false;							// Zurücksetzen der Hilfsvariable 
				Pos = ShootNorth(&first_hit);					// nördlich der ersten Koordinaten schießen
				return Pos;
			}
			else if ((first_hit.y + 1) <= 9)					// Kollision des nächsten Schusses mit südlichem Rand prüfen,
			{													// weil der Richtungswechsel nach Süden. Wenn Rand nicht erreicht -> i.O
				Direction = AttackDirection::S;					// Angriffsrichtung zu Süden wechseln
				Pos = ShootSouth(&first_hit);					// südlich der ersten Koordinaten schießen
				return Pos;
			}
			else												// Wäre der nächste Schuss ausserhalb des Spielfeldes
			{													// -> südlicher Spielfeldrand erreicht
				Direction = AttackDirection::E;					// die neue Angriffsrichtung ist Osten
				Pos = ShootEast(&first_hit);					// östlich der ersten Koordinaten schiessen
				return Pos;
			}
		}
		// Wenn die Angriffsrichtung bisher Süden war oder die nächsten Koordinaten ausserhalb des südlichen Randes (y>9) landen,
		// muss die Richtung nach Osten wechseln
		else if ((Direction == AttackDirection::S) || ((Direction == AttackDirection::S) && ((Pos.y + 1) > 9)))	
		{	
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true) 
			{
				FieldBorder = false;							// zurücksetzen der Hilfsvariable
				Pos = ShootSouth(&first_hit);					// südlich der ersten Koordinaten schießen
				return Pos;
			}
			else if (first_hit.x + 1 <= 9)						// Kollision des nächsten Schusses mit östlichen Rand prüfen,
			{													// weil der Richtungswechsel nach Osten. Wenn Rand nicht erreicht -> i.O
				Direction = AttackDirection::E;					// Angriffsrichtung zu Osten wechseln
				Pos = ShootEast(&first_hit);					// östlich der ersten Koordinaten schießen
				return Pos;
			}
			else												// Wäre der nächste Schuss ausserhalb des Spielfeldes
			{													// -> östlicher Spielfeldrand erreicht
				Direction = AttackDirection::W;					// Angriffsrichtung zu Westen wechseln
				Pos = ShootWest(&first_hit);					// westlich der ersten Koordinaten schießen
				return Pos;
			}
		}
		// Wenn die Angriffsrichtung bisher Osten war oder die nächsten Koordinaten ausserhalb des östlichen Randes (x>9) landen,
		// muss die Richtung nach Westen wechseln
		else if ((Direction == AttackDirection::E)	|| ((Direction == AttackDirection::E) && ((Pos.x + 1) > 9)))	
		{											
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{
				FieldBorder = false;							// zurücksetzen der Hilfsvariable
				Pos = ShootEast(&first_hit);					// östlich der ersten Koordinaten schießen
				return Pos;
			}
			else if (first_hit.x - 1 >= 0)						// Kollision des nächsten Schusses mit westlichen Rand prüfen,
			{													// weil der Richtungswechsel nach Westen. Wenn Rand nicht erreicht -> i.O
				Direction = AttackDirection::W;					// Angriffsrichtung zu Westen wechseln
				Pos = ShootWest(&first_hit);					// westlich der ersten Koordinaten schießen
				return Pos;
			}
			else												// Wäre der nächste Schuss ausserhalb des Spielfeldes
			{
				Direction = AttackDirection::N;					// Angriffsrichtung zu Norden wechseln
				alreadyShot = false;							// zurücksetzen der Hilfsvariablen
				DirectionChoice = false;						// zurücksetzen der Hilfsvariablen
				Pos = rndCoordinates();							// neue Zufallskoordinaten generieren
				alreadyShot = true;								
				first_hit = Pos;								// neue Koordinaten für den ersten Schuss
				return Pos;

			}
		}
		// Wenn die Angriffsrichtung bisher Westen war oder die nächsten Koordinaten ausserhalb des westlichen Randes (x<0) landen,
		// muss die Richtung nach Norden wechseln und neue Zufallskoordinaten generiert werden
		else if ((Direction == AttackDirection::W) || ((Direction == AttackDirection::W) && ((Pos.x - 1) < 0)))
		{
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{
				FieldBorder = false;							// zurücksetzen der Hilfsvariablen
				Pos = ShootWest(&first_hit);					// westlich der ersten Koordinaten schießen
				return Pos;
			}
			else												// Wurde schon nach Westen geschossen und das ging daneben
			{													// werden neue Zufallskoordinaten generitert
				alreadyShot = false;							// zurücksetzen der Hilfsvariablen
				Direction = AttackDirection::N;					// Angriffsrichtung zu Norden wechseln
				DirectionChoice = false;						// zurücksetzen der Hilfsvariablen

				Pos = rndCoordinates();							// Zufallskoordinaten generieren
				alreadyShot = true;
				first_hit = Pos;
				return Pos;
			}
		}
	}

	// Schiff suchen: 
	// Der letzter Schuss war ein Treffer UND es wurde schon geschossen
	if ((*LastShotHit == true) && (alreadyShot == true))
	{	
		// Die aktuelle Richtung ist Norden -> Schuss auf das Feld nördlich
		if ((Direction == AttackDirection::N))	
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{										// (wird hier vermutlich nicht nötig sein, da vor Norden nur Zufallswahl
				Pos = ShootNorth(&first_hit);		// nördlich der ersten Koordinaten schießen
				FieldBorder = false;				// zurücksetzen der Hilfsvariablen
				return Pos; 
			}
			else if ((Pos.y - 1) > 0)				// Liegt der nächste Schuss innerhalb des Spiefeldes und nicht am nördlichen Rand?
			{
				Pos = ShootNorth(&Pos);				// nördlich der letzten Koordinaten schießen
				return Pos;
			}
			else if ((Pos.y - 1) == 0)				// Liegt der nächste Schuss AUF dem nördlichen Rand? 
			{										
				Pos = ShootNorth(&Pos);				// nördlich der letzten Koordinaten schießen
				Direction = AttackDirection::S;		// Richtung zach Süden wechseln
				FieldBorder = true;					// Hilfsvariable für "Feldrand erreicht" setzen
				return Pos;
			}
			else if (Pos.y == 0)					// Liegt der letzte Schuss AUF dem nördlichen Rand?
			{
				Pos = ShootSouth(&first_hit);		// südlich der ersten Koordinaten schießen
				Direction = AttackDirection::S;		// Richtung nach Süden wechseln
				return Pos;
			}
		}
		// Die aktuelle Richtung ist Süden -> Schuss auf das Feld südlich
		else if ((Direction == AttackDirection::S))	
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{ 
				Pos = ShootSouth(&first_hit);		// südlich der ersten Koordinaten schießen
				FieldBorder = false;				// zurücksetzen der Hilfsvariablen
				return Pos; 
			}
			else if ((Pos.y + 1) < 9)				// Liegt der nächste Schuss innerhalb des Spielfeldes und nicht am südlichen Rand?
			{
				Pos = ShootSouth(&Pos);				// südlich der letzten Koordinaten schießen
				return Pos;
			}
			else if ((Pos.y + 1) == 9)				// Liegt der nächste Schuss AUF dem südlichen Rand?
			{
				Pos = ShootSouth(&Pos);				// südlich der letzten Koordinaten schießen
				Direction = AttackDirection::E;		// Richtung nach Osten wechseln
				FieldBorder = true;					// Hilfsvariable für "Feldrand erreicht" setzen
				return Pos;
			}
			else if (Pos.y == 9)					// Liegt der letzte Schuss AUF dem südlichen Rand?
			{
				if (Pos.x < 9)						// Liegt der letzte Schuss innerhalb des Spielfeldes (nicht am östlichen Rand)?
				{
					Pos = ShootEast(&first_hit);	// östlich der ersten Koordinaten schießen
					Direction = AttackDirection::E;	// Richtung nach Osten wechseln
					return Pos;
				}
				else if (Pos.x == 9)				// Liegt der letzte Schuss AUF dem östlichen Rand?
				{
					Pos = ShootWest(&first_hit);	// westlich der ersten Koordinaten schießen
					Direction = AttackDirection::W;	// Richtung nach Westen wechseln
					return Pos;
				}
			}
		}
		// Die aktuelle Richtung ist Osten -> Schuss auf das Feld östlich
		else if ((Direction == AttackDirection::E))
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{ 
				Pos = ShootEast(&first_hit);		// östlich der ersten Koordinaten schießen
				FieldBorder = false;				// zurücksetzen der Hilfsvariable
				return Pos; 
			}
			else if ((Pos.x + 1) < 9)				// Liegt der nächste Schuss innerhalb des Spielfeldes und nicht am östlichen Rand?
			{
				Pos = ShootEast(&Pos);				// östlich der letzten Koordinaten schießen
				return Pos;
			}
			else if ((Pos.x + 1) == 9)				// Liegt der nächste Schuss AUF dem östlichen Rand?
			{
				Pos = ShootEast(&Pos);				// östlich der letzten Koordinaten schießen
				Direction = AttackDirection::W;		// Richtung nach Westen wechseln
				FieldBorder = true;					// Hilfsvariable für "Feldrand erreicht" setzen
				return Pos;
			}
			else if (Pos.x == 9)					// Liegt der letzte Schuss AUF dem östlichen Rand?
			{
				Pos = ShootWest(&first_hit);		// westlich der ersten Koordinaten schießen
				Direction = AttackDirection::W;		// Richtung nach Westen wechseln
				return Pos;
			}
		}
		// Die aktuelle Richtung ist Westen -> Schuss auf das Feld westlich
		else if ((Direction == AttackDirection::W))
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{ 
				Pos = ShootWest(&first_hit);		// westlich der ersten Koordinaten schießen
				FieldBorder = false;				// zurücksetzen der Hilfsvariable
				return Pos; 
			}
			else if ((Pos.x - 1) > 0)				// Liegt der nächste Schuss innerhalb des Spielfeldes und nicht am westlichen Rand?
			{
				Pos = ShootWest(&Pos);				// westlich der letzten Koordinaten schießen
				return Pos;
			}
			else if ((Pos.x - 1) == 0)				// Liegt der nächste Schuss AUF dem westlichen Rand?
			{
				Pos = ShootWest(&Pos);				// westlich der letzten Koordinaten schießen
				return Pos;
			}
			else if (Pos.x == 0)					// Liegt der letzte Schuss AUF dem westlichen Rand?
			{
				Pos = rndCoordinates();				// neue Zufallskoordinaten generieren
				first_hit = Pos;					// neue erste Koordinaten
				alreadyShot = true;					// Hilfsvariablen setzen
				DirectionChoice = false;			// zurücksetzen von Hilfsvariablen 
				Direction = AttackDirection::N;		// Richtung nach Norden wechseln

			}
		}
	}
	return Pos;
}




/*


	// Test Strat4:
	Position Schuss = {};

	bool LastShotHit = false;
	bool blubb = false;

	for (int ii = 0; ii < 15; ii++)
	{
		Schuss = AttackStrategy4(&LastShotHit, &blubb);
		cout << "(" << (Schuss.x) << "," << (Schuss.y) << ")" << "  " << "Pew Pew" << endl;

		if (ii == 0)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl;
		}
		else if (ii == 1)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl;
		}
		else if (ii == 2)
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl;
		}
		else if (ii == 3)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl;
		}
		else if (ii == 4)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = true;
		}
		else if (ii == 5)
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl; blubb = false;
		}
		else if (ii == 6)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = false;
		}
		else if (ii == 7)
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl; blubb = false;
		}
		else if (ii == 8)
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl; blubb = false;
		}
		else if (ii == 9)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = false;
		}
		else if (ii == 10)
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl; blubb = false;
		}
		else if (ii == 11)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = false;
		}
		else if (ii == 12)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = false;
		}
		else
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl; blubb = false;
		}
		;
	}

*/