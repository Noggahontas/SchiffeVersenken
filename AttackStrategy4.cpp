#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "AttackStrategy4.h"
#include <time.h>

using namespace std;

/*
TODO:	- macht noch Probleme, wenn Koordinaten in den Eckpunkten liegen oder am Rand der aktuellen Richtung 
		  (zB erster Schuss auf y=0 und n�rdliche Richtung -> doofe Dinge passieren)
		

-----------------------------------------------------------------------------------------------------------------------
Angriffsstrategie 4:

	->	Strategie soll zuf�llige Punkte angreifen.
		

		Bei einem Treffer wird zuerst die Ausrichtung des Schiffes gesucht (hei�t einfach die Schussrichtung 
		in einer bestimmten Reihenfolge abgearbeitet):
			Schuss n�rdlich von den Startkoordinaten,
				wenn hit, wieder n�rdlicher Schuss -> bis miss oder Feldrand
				wenn miss, s�dlich der Startkoordinaten
					wenn hit, wieder s�dlicher Schuss -> bis miss oder Feldrand
					wenn miss, �stlich der Startkoordinaten
						wenn hit, wieder �stlicher Schuss -> bis miss oder Feldrand
						wenn miss, westlich der Startkoordinaten
							wenn hit, wieder westlicher Schuss -> bis miss oder Feldrand
							wenn miss, neue RND-Koordinaten und von vorne starten (Norden -> S�den -> Osten -> Westen)
	 X
	 X
 X X X X X
	 X
	 X
*/

// Ausgelaugerte "Berechnung" der n�chsten Koordinaten:
Position ShootNorth(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x;
	new_Pos.y = previous_Position->y - 1;
	return new_Pos;
}

Position ShootSouth(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x;
	new_Pos.y = previous_Position->y + 1;
	return new_Pos;
}

Position ShootEast(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x + 1;
	new_Pos.y = previous_Position->y;
	return new_Pos;
}

Position ShootWest(Position* previous_Position)
{
	Position new_Pos = {};
	new_Pos.x = previous_Position->x - 1;
	new_Pos.y = previous_Position->y;
	return new_Pos;
}

// Berechnung neuer Koordinaten:
Position rndCoordinates()
{
	Position new_pos = {};
	cout << "Random: ";
	new_pos.x = (rand() % 10);
	new_pos.y = (rand() % 10);
	return new_pos;
}

Position AttackStrategy4(bool* LastShotHit, bool *blubb)
{
	// bool LastShotHit -> Information, ob etwas getroffen wurde mit dem letzte Schuss
	static Position Pos = { };
	static bool alreadyShot = false;			// Wenn schonmal geschossen wurde (true), f�r bestimmte Abfragen

	static AttackDirection Direction;			// zeigt die Angriffsrichtung an f�r die n�chsten Koordinaten
	static bool DirectionChoice = false;		// zum Unterscheiden zwischen neuen rnd-Koords und Richtungswechselabfrage

	bool FieldBorder = false;					// Spielfeldrandabfrage
	
	static Position first_hit = {};				// merken des ersten Schusses (die ersten rnd-Koordinaten jedes Durchlaufes)
	
	if (*blubb == true) 
	{ 
		cout << "Versenkt." << endl; 
		alreadyShot = false;						
		Direction = AttackDirection::N;
		DirectionChoice = false;
	}
	

	// Erster Schuss (Bedingungen: x und y = NULL) -> Random-Koordinaten
	// vorheriger Schuss ging daneben + es wurde schon geschossen + Richtung noch nicht gew�hlt -> neue Random-Koordinaten 
	if (((Pos.x == NULL) && (Pos.y == NULL)) || ((*LastShotHit == false) && (alreadyShot == true) && (!DirectionChoice)) || (*blubb == true))
	{
		Pos = rndCoordinates();
		alreadyShot = true;
		first_hit = Pos;
		return Pos;
	}

	// Random-Koordinaten waren ein Treffer, dann kann die "Schiffsuche" starten (zuerst Richtung Norden bis daneben etc.)
	if ((*LastShotHit == true) && (alreadyShot == true) && (!DirectionChoice))
	{
		Direction = AttackDirection::N;
		DirectionChoice = true;
		cout << "Richtung \"Norden\" aktivieren. " << endl;
	}


	// Wurde geschossen, aber nicht getroffen -> muss die Richtung gewechselt werden
	if (((*LastShotHit == false) && (alreadyShot)))
	{	// Richtung war bisher Norden oder Koordinaten auf dem n�rdlichen Rand (y=0) -> Richtung wechselt jetzt nach S�den
		if ((Direction == AttackDirection::N) || ((Direction == AttackDirection::N) && ((Pos.y - 1) < 0)))	
		{	// Kollision unterhalb der Startkoordinaten mit s�dlichem Rand pr�fen																				
			if (first_hit.y + 1 <= 9)
			{
				cout << "Richtung von Norden nach Sueden aendern." << endl;
				Direction = AttackDirection::S;
				Pos = ShootSouth(&first_hit);
				return Pos;
			}
			else // S�dlicher Rand erreicht -> weiter Richtung Osten
			{
				Direction = AttackDirection::E;
				Pos = ShootEast(&first_hit);
				return Pos;
			}
		}
		// Richtung war bisher S�den oder Koordinaten auf dem s�dlichen Rand (y=9) -> Richtung wechselt jetzt nach Osten
		else if ((Direction == AttackDirection::S) || ((Direction == AttackDirection::S) && ((Pos.y + 1) > 9)))	
		{	// Kollision rechts von Startkoordinaten mit �stlichem Rand pr�fen										
			if (first_hit.x + 1 <= 9)
			{
				cout << "Richtung von Sueden nach Osten aendern." << endl;
				Direction = AttackDirection::E;
				Pos = ShootEast(&first_hit);
				return Pos;
			}
			else	// �stlicher Rand erreicht -> weiter Richtung Westen
			{
				Direction = AttackDirection::W;
				Pos = ShootWest(&first_hit);
				return Pos;
			}
		}
		// Richtung war bisher Osten oder Koordinaten auf dem �stlichen Rand (x=9) -> Richtung wechselt jetzt nach Westen
		else if ((Direction == AttackDirection::E)	|| ((Direction == AttackDirection::E) && ((Pos.x + 1) > 9)))	
		{	// Kollision lunks von Startkoordinaten mit westlichem Rand pr�fen											
			if (first_hit.x - 1 >= 0)
			{
				cout << "Richtung von Osten nach Westen aendern." << endl;
				Direction = AttackDirection::W;
				Pos = ShootWest(&first_hit);
				return Pos;
			}
			else	// Westlicher Rand erreicht -> weiter mit neuen rnd-Koordinaten
			{
				Direction = AttackDirection::N;
				alreadyShot = false;
				DirectionChoice = false;
				Pos = rndCoordinates();
				alreadyShot = true;
				first_hit = Pos;
				return Pos;

			}
		}// Richtung war bisher Westen oder Koordinaten auf dem westlichen Rand (x=0) -> neue rnd-Koordinaten
		else if ((Direction == AttackDirection::W) || ((Direction == AttackDirection::W) && ((Pos.x - 1) < 0)))
		{

			cout << "Richtung von Westen nach Neustart aendern." << endl;
			alreadyShot = false;						// nachdem West-Richtung fertig abgearbeitet, wieder alles zur�cksetzen -> neue rnd Koords
			Direction = AttackDirection::N;
			DirectionChoice = false;

			Pos = rndCoordinates();
			alreadyShot = true;
			first_hit = Pos;
			return Pos;
		}
	}

	// Schiff suchen: 
	// erste Bedingungen: letzter Schuss war ein Treffer und es wurde schon geschossen
	if ((*LastShotHit == true) && (alreadyShot == true))
	{	
		// zweite Bedingung: aktuelle Richtung ist Norden -> Schuss auf das Feld n�rdlich
		if ((Direction == AttackDirection::N))	
		{
			if (FieldBorder)						// vorheriger Schuss war auf Feldrand
			{ 
				Pos = ShootNorth(&first_hit); 
				FieldBorder = false; 
				return Pos; 
			}
			else if (Pos.y - 1 > 0)					// Kollision mit n�rdlichem Rand pr�fen
			{
				Pos = ShootNorth(&Pos);
				return Pos;
			}
			else if ((Pos.y - 1) == 0)				// n�rdlicher Rand -> Richtungswechsel notwendig -> S�den
			{
				Pos = ShootNorth(&Pos);
				Direction = AttackDirection::S;
				FieldBorder = true;
				return Pos;
			}
			else if (Pos.y == 0)					// wenn schon am Rand, muss hier der Richtungswechsel her
			{
				cout << "1. Vergessen was hier her kommt. ��h...Selbstzerst�rung aktiviert..." << endl;
			}
		}
		// zweite Bedingung: aktuelle Richtung ist S�den -> Schuss auf das Feld s�dlich
		else if ((Direction == AttackDirection::S))	
		{
			if (FieldBorder)						// vorheriger Schuss war auf Feldrand
			{ 
				Pos = ShootSouth(&first_hit); 
				FieldBorder = false; 
				return Pos; 
			}
			else if (Pos.y + 1 < 9)					// Kollision mit s�dlichem Feldrand pr�fen
			{
				Pos = ShootSouth(&Pos);
				return Pos;
			}
			else if ((Pos.y + 1) == 9)				// s�dlicher Rand -> Richtungswechsel -> Osten
			{
				Pos = ShootSouth(&Pos);
				Direction = AttackDirection::E;
				FieldBorder = true;
				return Pos;
			}
			else if (Pos.y == 9)					// wenn schon am Rand, muss hier der Richtungswechsel her
			{
				cout << "2. Vergessen was hier her kommt. ��h...Selbstzerst�rung aktiviert..." << endl;
			}
		}
		// zweite Bedingung: aktuelle Richtung ist Osten und Feldrand noch nicht erreicht -> Schuss auf das Feld �stlich
		else if ((Direction == AttackDirection::E))
		{
			if (FieldBorder)						// vorheriger Schuss war auf Feldrand
			{ 
				Pos = ShootEast(&first_hit); 
				FieldBorder = false; 
				return Pos; 
			}
			else if (Pos.x + 1 < 9)					// Kollision mit �stlichem Feldrand pr�fen
			{
				Pos = ShootEast(&Pos);
				return Pos;
			}
			else if ((Pos.x + 1) == 9)				// �stlicher Rand -> Richtungswechsel -> Westen 
			{
				Pos = ShootEast(&Pos);
				Direction = AttackDirection::W;
				FieldBorder = true;
				return Pos;
			}
			else if (Pos.x == 9)					// wenn schon am Rand, muss hier der Richtungswechsel her
			{
				cout << "3. Vergessen was hier her kommt. ��h...Selbstzerst�rung aktiviert..." << endl;
			}
		}
		// zweite Bedingung: aktuelle Richtung ist Westen -> Schuss auf das Feld westlich
		else if ((Direction == AttackDirection::W))
		{
			if (FieldBorder)						// vorheriger Schuss war auf Feldrand 
			{ 
				Pos = ShootWest(&first_hit); 
				FieldBorder = false; 
				return Pos; 
			}
			else if (Pos.x - 1 > 0)					// Kollision mit westlichem Feldrand pr�fen
			{
				Pos = ShootWest(&Pos);
				return Pos;
			}
			else if ((Pos.x - 1) == 0)				// westlicher Feldrand -> anschliessend neue rnd-Koordinaten
			{
				Pos = ShootWest(&Pos);
				return Pos;
			}
			else if (Pos.x == 0)					// wenn schon am Rand, muss hier der Richtungswechsel her
			{
				Pos = rndCoordinates();
				first_hit = Pos;
				alreadyShot = true;
				DirectionChoice = false;
				Direction = AttackDirection::N;

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

	for (int ii = 0; ii < 8; ii++)
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
		else if (ii == 3)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = true;
		}
		else if (ii == 2)
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl;
		}
		else if (ii == 4)
		{
			LastShotHit = true; cout << ii << ": Schuss hat getroffen." << endl; blubb = false;
		}
		else
		{
			LastShotHit = false; cout << ii << ": Schuss ging daneben." << endl;
		}
		;
	}

*/