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

	- Strategie w�hlt zuf�llige Punkte, falls kein Schiff gesucht wird
		
		Bei einem Treffer der Zufallskoordinaten wird zuerst die Ausrichtung des Schiffes gesucht 
		(hei�t einfach die Schussrichtung in einer bestimmten Reihenfolge abgearbeitet):
			Schuss n�rdlich von den Startkoordinaten,
				wenn hit, wieder n�rdlicher Schuss -> bis miss oder Feldrand
				wenn miss oder Feldrand, s�dlich der Startkoordinaten
					wenn hit, wieder s�dlicher Schuss -> bis miss oder Feldrand
					wenn miss oder Feldrand, �stlich der Startkoordinaten
						wenn hit, wieder �stlicher Schuss -> bis miss oder Feldrand
						wenn miss oder Feldrand, westlich der Startkoordinaten
							wenn hit, wieder westlicher Schuss -> bis miss oder Feldrand
							wenn miss oder Feldrand, neue Zufallskoordinaten und von vorne starten (Norden -> S�den -> Osten -> Westen)
		Wird zwischendurch ein Schiff versenkt, beginnt die Strategie von vorn mit Zufallskoordinaten.

		Strategie ben�tigt als �bergabeparameter die Information, ob der letzte eigene Schuss ein Treffer war (LastShotHit)
		und ob das grade beschossene Schiff versenkt wurde (sunk).
		

*/

// Ausgelagerte "Berechnung" der n�chsten Koordinaten:

// Sch�sse nach Norden �ndern den x-Wert nicht, der y-Wert wird dekrementiert: x=x und y=y-1
Position ShootNorth(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x;
	new_Pos.y = previous_Position->y - 1;
	return new_Pos;
}

// Sch�sse nach S�den �ndern den x-Wert nicht, der y-Wert wird inkrementiert: x=x und y=y+1
Position ShootSouth(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x;
	new_Pos.y = previous_Position->y + 1;
	return new_Pos;
}

// Sch�sse nach Osten �ndern den y-Wert nicht, der x-Wert wird inkrementiert: y=y und x=x+1
Position ShootEast(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x + 1;
	new_Pos.y = previous_Position->y;
	return new_Pos;
}
// Sch�sse nach Westen �ndern den y-Wert nicht, der x-Wert wird dekrementiert: y=y und x=x-1
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
	static bool alreadyShot = false;			// Wenn schonmal geschossen wurde (true) -> f�r bestimmte Abfragen

	static AttackDirection Direction;			// zeigt die Angriffsrichtung an f�r den n�chsten
	static bool DirectionChoice = false;		// zur Unterscheidung zwischen neuen rnd-Koordinaten und Richtungswechselabfrage

	static bool FieldBorder = false;			// Kollision mit dem Spielfeldrand muss gesondert behandelt werden
	
	static Position first_hit = {};				// merken des ersten Schusses (die ersten rnd-Koordinaten bei jeder Suchfolge)
	
	
	// Erster Schuss (Bedingungen: x und y = NULL) -> rnd-Koordinaten zur�ckgeben
	// ODER
	// Ging vorherige Schuss daneben UND es wurde schon geschossen UND Richtung noch nicht gew�hlt -> neue rnd-Koordinaten zur�ckgeben
	// ODER
	// Der vorherhige Schuss hat ein Schiff versenkt -> neue rnd-Koordinaten zur�ckgeben
	if (((Pos.x == NULL) && (Pos.y == NULL)) || ((*LastShotHit == false) && (alreadyShot == true) && (!DirectionChoice)) || (*sunk == true))
	{
		if (*sunk == true)							// Falls das angegriffene Schiff des vorherigen Schusses versenkt wirde
		{											// werden bestimmte Hilfsvariablen zur�ckgesetzt
			DirectionChoice = false;
		}
		Direction = AttackDirection::N;				// erste Angriffsrichtung ist immer Norden
		Pos = rndCoordinates();						// Zufallskoordinaten generieren
		alreadyShot = true;							// Hilfsvariable setzen
		first_hit = Pos;							// Zufalskoordinaten werden in first_hit geschrieben -> wird beim Richtungswechsel ben�tigt
		return Pos;									// neue Angriffskoordinaten zur�ckgeben
	}

	// Waren Zufallskoordinaten ein Treffer UND es wurde auch geschossen UND die Angriffsrichtung wurde gew�hlt,
	// dann kann die "Schiffsuche" starten (zuerst Richtung Norden)
	if ((*LastShotHit == true) && (alreadyShot == true) && (!DirectionChoice))
	{
		Direction = AttackDirection::N;
		DirectionChoice = true;
	}


	
	// Wenn der letzte Schuss nicht getroffen hat, aber geschossen wurde, muss die Richtung gewechselt werden, 
	// abh�ngig von der aktuell aktiven Richtung. 
	// (Wenn z.B. beim schie�en in Richtung S�den ein Schuss daneben geht, 
	// muss die Richtung nach Osten gewechselt werden.)
	if (((*LastShotHit == false) && (alreadyShot)))
	{	// Wenn die Angriffsrichtung bisher Norden war oder die n�chsten Koordinaten ausserhalb des n�rdlichen Randes (y<0) landen,
		// muss die Richtung nach S�den wechseln
		if ((Direction == AttackDirection::N) || ((Direction == AttackDirection::N) && ((Pos.y - 1) < 0)))	
		{	
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true) 
			{													// (wird hier vermutlich nicht n�tig sein, da vor Norden nur Zufallswahl kommt) 
				FieldBorder = false;							// Zur�cksetzen der Hilfsvariable 
				Pos = ShootNorth(&first_hit);					// n�rdlich der ersten Koordinaten schie�en
				return Pos;
			}
			else if ((first_hit.y + 1) <= 9)					// Kollision des n�chsten Schusses mit s�dlichem Rand pr�fen,
			{													// weil der Richtungswechsel nach S�den. Wenn Rand nicht erreicht -> i.O
				Direction = AttackDirection::S;					// Angriffsrichtung zu S�den wechseln
				Pos = ShootSouth(&first_hit);					// s�dlich der ersten Koordinaten schie�en
				return Pos;
			}
			else												// W�re der n�chste Schuss ausserhalb des Spielfeldes
			{													// -> s�dlicher Spielfeldrand erreicht
				Direction = AttackDirection::E;					// die neue Angriffsrichtung ist Osten
				Pos = ShootEast(&first_hit);					// �stlich der ersten Koordinaten schiessen
				return Pos;
			}
		}
		// Wenn die Angriffsrichtung bisher S�den war oder die n�chsten Koordinaten ausserhalb des s�dlichen Randes (y>9) landen,
		// muss die Richtung nach Osten wechseln
		else if ((Direction == AttackDirection::S) || ((Direction == AttackDirection::S) && ((Pos.y + 1) > 9)))	
		{	
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true) 
			{
				FieldBorder = false;							// zur�cksetzen der Hilfsvariable
				Pos = ShootSouth(&first_hit);					// s�dlich der ersten Koordinaten schie�en
				return Pos;
			}
			else if (first_hit.x + 1 <= 9)						// Kollision des n�chsten Schusses mit �stlichen Rand pr�fen,
			{													// weil der Richtungswechsel nach Osten. Wenn Rand nicht erreicht -> i.O
				Direction = AttackDirection::E;					// Angriffsrichtung zu Osten wechseln
				Pos = ShootEast(&first_hit);					// �stlich der ersten Koordinaten schie�en
				return Pos;
			}
			else												// W�re der n�chste Schuss ausserhalb des Spielfeldes
			{													// -> �stlicher Spielfeldrand erreicht
				Direction = AttackDirection::W;					// Angriffsrichtung zu Westen wechseln
				Pos = ShootWest(&first_hit);					// westlich der ersten Koordinaten schie�en
				return Pos;
			}
		}
		// Wenn die Angriffsrichtung bisher Osten war oder die n�chsten Koordinaten ausserhalb des �stlichen Randes (x>9) landen,
		// muss die Richtung nach Westen wechseln
		else if ((Direction == AttackDirection::E)	|| ((Direction == AttackDirection::E) && ((Pos.x + 1) > 9)))	
		{											
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{
				FieldBorder = false;							// zur�cksetzen der Hilfsvariable
				Pos = ShootEast(&first_hit);					// �stlich der ersten Koordinaten schie�en
				return Pos;
			}
			else if (first_hit.x - 1 >= 0)						// Kollision des n�chsten Schusses mit westlichen Rand pr�fen,
			{													// weil der Richtungswechsel nach Westen. Wenn Rand nicht erreicht -> i.O
				Direction = AttackDirection::W;					// Angriffsrichtung zu Westen wechseln
				Pos = ShootWest(&first_hit);					// westlich der ersten Koordinaten schie�en
				return Pos;
			}
			else												// W�re der n�chste Schuss ausserhalb des Spielfeldes
			{
				Direction = AttackDirection::N;					// Angriffsrichtung zu Norden wechseln
				alreadyShot = false;							// zur�cksetzen der Hilfsvariablen
				DirectionChoice = false;						// zur�cksetzen der Hilfsvariablen
				Pos = rndCoordinates();							// neue Zufallskoordinaten generieren
				alreadyShot = true;								
				first_hit = Pos;								// neue Koordinaten f�r den ersten Schuss
				return Pos;

			}
		}
		// Wenn die Angriffsrichtung bisher Westen war oder die n�chsten Koordinaten ausserhalb des westlichen Randes (x<0) landen,
		// muss die Richtung nach Norden wechseln und neue Zufallskoordinaten generiert werden
		else if ((Direction == AttackDirection::W) || ((Direction == AttackDirection::W) && ((Pos.x - 1) < 0)))
		{
			if (FieldBorder)									// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{
				FieldBorder = false;							// zur�cksetzen der Hilfsvariablen
				Pos = ShootWest(&first_hit);					// westlich der ersten Koordinaten schie�en
				return Pos;
			}
			else												// Wurde schon nach Westen geschossen und das ging daneben
			{													// werden neue Zufallskoordinaten generitert
				alreadyShot = false;							// zur�cksetzen der Hilfsvariablen
				Direction = AttackDirection::N;					// Angriffsrichtung zu Norden wechseln
				DirectionChoice = false;						// zur�cksetzen der Hilfsvariablen

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
		// Die aktuelle Richtung ist Norden -> Schuss auf das Feld n�rdlich
		if ((Direction == AttackDirection::N))	
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{										// (wird hier vermutlich nicht n�tig sein, da vor Norden nur Zufallswahl
				Pos = ShootNorth(&first_hit);		// n�rdlich der ersten Koordinaten schie�en
				FieldBorder = false;				// zur�cksetzen der Hilfsvariablen
				return Pos; 
			}
			else if ((Pos.y - 1) > 0)				// Liegt der n�chste Schuss innerhalb des Spiefeldes und nicht am n�rdlichen Rand?
			{
				Pos = ShootNorth(&Pos);				// n�rdlich der letzten Koordinaten schie�en
				return Pos;
			}
			else if ((Pos.y - 1) == 0)				// Liegt der n�chste Schuss AUF dem n�rdlichen Rand? 
			{										
				Pos = ShootNorth(&Pos);				// n�rdlich der letzten Koordinaten schie�en
				Direction = AttackDirection::S;		// Richtung zach S�den wechseln
				FieldBorder = true;					// Hilfsvariable f�r "Feldrand erreicht" setzen
				return Pos;
			}
			else if (Pos.y == 0)					// Liegt der letzte Schuss AUF dem n�rdlichen Rand?
			{
				Pos = ShootSouth(&first_hit);		// s�dlich der ersten Koordinaten schie�en
				Direction = AttackDirection::S;		// Richtung nach S�den wechseln
				return Pos;
			}
		}
		// Die aktuelle Richtung ist S�den -> Schuss auf das Feld s�dlich
		else if ((Direction == AttackDirection::S))	
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{ 
				Pos = ShootSouth(&first_hit);		// s�dlich der ersten Koordinaten schie�en
				FieldBorder = false;				// zur�cksetzen der Hilfsvariablen
				return Pos; 
			}
			else if ((Pos.y + 1) < 9)				// Liegt der n�chste Schuss innerhalb des Spielfeldes und nicht am s�dlichen Rand?
			{
				Pos = ShootSouth(&Pos);				// s�dlich der letzten Koordinaten schie�en
				return Pos;
			}
			else if ((Pos.y + 1) == 9)				// Liegt der n�chste Schuss AUF dem s�dlichen Rand?
			{
				Pos = ShootSouth(&Pos);				// s�dlich der letzten Koordinaten schie�en
				Direction = AttackDirection::E;		// Richtung nach Osten wechseln
				FieldBorder = true;					// Hilfsvariable f�r "Feldrand erreicht" setzen
				return Pos;
			}
			else if (Pos.y == 9)					// Liegt der letzte Schuss AUF dem s�dlichen Rand?
			{
				if (Pos.x < 9)						// Liegt der letzte Schuss innerhalb des Spielfeldes (nicht am �stlichen Rand)?
				{
					Pos = ShootEast(&first_hit);	// �stlich der ersten Koordinaten schie�en
					Direction = AttackDirection::E;	// Richtung nach Osten wechseln
					return Pos;
				}
				else if (Pos.x == 9)				// Liegt der letzte Schuss AUF dem �stlichen Rand?
				{
					Pos = ShootWest(&first_hit);	// westlich der ersten Koordinaten schie�en
					Direction = AttackDirection::W;	// Richtung nach Westen wechseln
					return Pos;
				}
			}
		}
		// Die aktuelle Richtung ist Osten -> Schuss auf das Feld �stlich
		else if ((Direction == AttackDirection::E))
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{ 
				Pos = ShootEast(&first_hit);		// �stlich der ersten Koordinaten schie�en
				FieldBorder = false;				// zur�cksetzen der Hilfsvariable
				return Pos; 
			}
			else if ((Pos.x + 1) < 9)				// Liegt der n�chste Schuss innerhalb des Spielfeldes und nicht am �stlichen Rand?
			{
				Pos = ShootEast(&Pos);				// �stlich der letzten Koordinaten schie�en
				return Pos;
			}
			else if ((Pos.x + 1) == 9)				// Liegt der n�chste Schuss AUF dem �stlichen Rand?
			{
				Pos = ShootEast(&Pos);				// �stlich der letzten Koordinaten schie�en
				Direction = AttackDirection::W;		// Richtung nach Westen wechseln
				FieldBorder = true;					// Hilfsvariable f�r "Feldrand erreicht" setzen
				return Pos;
			}
			else if (Pos.x == 9)					// Liegt der letzte Schuss AUF dem �stlichen Rand?
			{
				Pos = ShootWest(&first_hit);		// westlich der ersten Koordinaten schie�en
				Direction = AttackDirection::W;		// Richtung nach Westen wechseln
				return Pos;
			}
		}
		// Die aktuelle Richtung ist Westen -> Schuss auf das Feld westlich
		else if ((Direction == AttackDirection::W))
		{
			if (FieldBorder)						// vorheriger Schuss war auf einem Feldrand (FieldBorder = true)
			{ 
				Pos = ShootWest(&first_hit);		// westlich der ersten Koordinaten schie�en
				FieldBorder = false;				// zur�cksetzen der Hilfsvariable
				return Pos; 
			}
			else if ((Pos.x - 1) > 0)				// Liegt der n�chste Schuss innerhalb des Spielfeldes und nicht am westlichen Rand?
			{
				Pos = ShootWest(&Pos);				// westlich der letzten Koordinaten schie�en
				return Pos;
			}
			else if ((Pos.x - 1) == 0)				// Liegt der n�chste Schuss AUF dem westlichen Rand?
			{
				Pos = ShootWest(&Pos);				// westlich der letzten Koordinaten schie�en
				return Pos;
			}
			else if (Pos.x == 0)					// Liegt der letzte Schuss AUF dem westlichen Rand?
			{
				Pos = rndCoordinates();				// neue Zufallskoordinaten generieren
				first_hit = Pos;					// neue erste Koordinaten
				alreadyShot = true;					// Hilfsvariablen setzen
				DirectionChoice = false;			// zur�cksetzen von Hilfsvariablen 
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