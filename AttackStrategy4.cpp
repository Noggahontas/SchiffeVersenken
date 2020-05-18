#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "AttackStrategy4.h"
#include <time.h>

using namespace std;

/*
TODO:	- macht noch Probleme, wenn der erste Schuss am Feldrand liegt -> die neu generierten Koordinaten abfragen, 
		  bevor sie zurückgegeben werden, bei Randkollision neue berechnen. Und nicht die alten Koordinaten prüfen
		- ordentliche Variablennamen 
		- eventuell die bool Sammlungen als struct oder andere, bessere Möglichkeit finden
		- bool-Armee für die Himmelsrichtungen durch die schon vorhande enum class AttackDirection ersetzen
		- 

-----------------------------------------------------------------------------------------------------------------------
Angriffsstrategie 4:

	->	Strategie soll bestimmte feste Punkte (nicht so cool) oder zufällige Punkte angreifen.
		Wenn zufällig, dann eventuell Feld in zwei Hälften/vier Quadranten einteilen für bessere Verteilung (noch nicht realisiert!).

		Bei einem Treffer wird zuerst die Ausrichtung des Schiffes gesucht (heißt einfach die Schussrichtung 
		in einer bestimmten Reihenfolge abgearbeitet):
			Schuss nördlich von den Startkoordinaten,
				wenn hit, wieder nördlicher Schuss -> bis miss oder Feldrand
				wenn miss, südlich der Startkoordinaten
					wenn hit, wieder südlicher Schuss -> bis miss oder Feldrand
					wenn miss, östlich der Startkoordinaten
						wenn hit, wieder östlicher Schuss -> bis miss oder Feldrand
						wenn miss, westlich der Startkoordinaten
							wenn hit, wieder westlicher Schuss -> bis miss oder Feldrand
							wenn miss, neue RND-Koordinaten und von vorne starten (Norden -> Süden -> Osten -> Westen)
	 X
	 X
 X X X X X
	 X
	 X
*/

// Ausgelaugerte "Berechnung" der nächsten Koordinaten:
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

Position AttackStrategy4(Position* previous_Position, bool* LastShotHit) // bool *versenkt
{
	// bool LastShotHit -> brauche die Information vong Norrer, ob etwas getroffen wurde mit letzte Schuss
	
	static bool alreadyShot = false;	// Wenn schonmal geschossen wurde (true), für bestimmte Abfragen

	// Zeigt an, in welche Richtung geschossen (Auswahl der nächsten Koordinaten) werden soll
	// kann noch durch enum class AttackDirection ersetzt werden, wenns eh schon da ist:
	// static AttackDirection Direction;
	static bool richtung_norden = false;
	static bool richtung_sueden = false;
	static bool richtung_osten = false;
	static bool richtung_westen = false;
	static bool DirectionChoice = false;		// zum Unterscheiden zwischen neuen rnd-Koords und Richtungswechselabfrage


	bool FieldBorder = false;
	bool FieldBorderNorth = false;
	bool FieldBorderSouth = false;
	bool FieldBorderWest = false;
	bool FieldBorderEast = false;

	static Position first_hit = {};
	Position new_Position = {};

	// Erster Schuss (Bedingungen: x und y = NULL) -> Random-Koordinaten
	// vorheriger Schuss ging daneben + es wurde schon geschossen + Richtung noch nicht gewählt -> neue Random-Koordinaten 
	if (((previous_Position->x == NULL) && (previous_Position->y == NULL)) || ((*LastShotHit == false) && (alreadyShot == true) && (DirectionChoice == false)))
	{
		new_Position = rndCoordinates();
		
		alreadyShot = true;
		first_hit = new_Position;
		return new_Position;
	}

	// Random-Koordinaten waren ein Treffer, dann kann die "Schiffsuche" starten (zuerst Richtung Norden bis daneben etc)
	if ((*LastShotHit == true) && (alreadyShot == true) && (!DirectionChoice))
	{
		richtung_norden = true;
		DirectionChoice = true;
		cout << "Richtung \"Norden\" aktivieren. " << endl;
	}

	// Feldrand-Kollision prüfen 
	// TODO: hier nicht die letzten, sondern die neuen Koordinaten abfragen, bevor sie zurückgegeben werden
	if (previous_Position->y == 0) { FieldBorderNorth = true; FieldBorder = true; cout << "Feldrand Norden erreicht." << endl; }
	else if (previous_Position->y == 9) { FieldBorderSouth = true; FieldBorder = true; cout << "Feldrand Sueden erreicht." << endl;}
	else if (previous_Position->x == 0) { FieldBorderWest = true; FieldBorder = true; cout << "Feldrand Westen erreicht." << endl;}
	else if (previous_Position->x == 9) { FieldBorderEast = true; FieldBorder = true; cout << "Feldrand Osten erreicht." << endl;}
	

	// Wurde geschossen, aber nicht getroffen || Feldrand erreicht -> muss die Richtung gewechselt werden
	if (((*LastShotHit == false) && (alreadyShot)) || (FieldBorder == true))
	{
		if (richtung_norden == true)	// Richtung war bisher Norden, wechselst jetzt zu Sueden und setzt die neuen Koordinaten
		{								// auf das Feld suedlich des ersten Treffers
			cout << "Richtung von Norden nach Sueden aendern." << endl;
			richtung_norden = false;
			richtung_sueden = true;
			new_Position.x = first_hit.x;
			new_Position.y = first_hit.y + 1;
			return new_Position;
		}
		else if (richtung_sueden == true)	// Richtung war bisher Sueden, wechselt jetzt zu Osten und setzt die neuen Koordinaten
		{									// auf das Feld oestlich des ersten Treffers
			cout << "Richtung von Sueden nach Osten aendern." << endl;
			richtung_sueden = false;
			richtung_osten = true;
			new_Position.x = first_hit.x + 1;
			new_Position.y = first_hit.y;
			return new_Position;
		}
		else if (richtung_osten == true)	// Richtung war bisher Osten, wechselt jetzt zu Westen und setzt die neuen Koordinaten
		{									// auf das Feld westlich des ersten Treffers
			cout << "Richtung von Osten nach Westen aendern." << endl;
			richtung_osten = false;
			richtung_westen = true;
			new_Position.x = first_hit.x - 1;
			new_Position.y = first_hit.y;
			return new_Position;
		}
		else
		{
			cout << "Richtung von Westen nach Neustart aendern." << endl;
			alreadyShot = false;		// nachdem West-Richtung fertig abgearbeitet, wieder alles zurücksetzen -> neue rnd Koords
			richtung_westen = false;
			FieldBorder = false;
			FieldBorderNorth = false;
			FieldBorderSouth = false;
			FieldBorderWest = false;
			FieldBorderEast = false;
			DirectionChoice = false;

			new_Position = rndCoordinates();
			alreadyShot = true;
			first_hit = new_Position;
			return new_Position;
		}
	}

	// Schiff suchen: 
	// erste Bedingungen: letzter Schuss war ein Treffer und es wurde schon geschossen
	if ((*LastShotHit == true) && (alreadyShot == true))
	{	
		// zweite Bedingung: aktuelle Richtung ist Norden und Feldrand noch nicht erreicht -> Schuss auf das Feld nördlich
		if ((richtung_norden == true) && (!FieldBorderNorth))
		{
			new_Position = ShootNorth(previous_Position);
			return new_Position;
		}
		// zweite Bedingung: aktuelle Richtung ist Süden und Feldrand noch nicht erreicht -> Schuss auf das Feld südlich
		if ((richtung_sueden == true) && (!FieldBorderSouth))
		{
			new_Position = ShootSouth(previous_Position);
			return new_Position;
		}
		// zweite Bedingung: aktuelle Richtung ist Osten und Feldrand noch nicht erreicht -> Schuss auf das Feld östlich
		if ((richtung_osten == true) && (!FieldBorderEast))
		{
			new_Position = ShootEast(previous_Position);
			return new_Position;
		}
		// zweite Bedingung: aktuelle Richtung ist Westen und Feldrand noch nicht erreicht -> Schuss auf das Feld westlich
		if ((richtung_westen == true) && (!FieldBorderWest))
		{
			new_Position = ShootWest(previous_Position);
			return new_Position;
		}
	}
	return new_Position;
}




/*

// Test Strat4:
	Position Schuss = {};
	bool das_war_ein_treffer = false;
	for (int ii = 0; ii < 6; ii++)
	{
		Schuss = AttackStrategy4(&Schuss, &das_war_ein_treffer);
		cout << "(" << (Schuss.x) << "," << (Schuss.y) << ")" << "  " << "Pew Pew" << endl;

		if (ii == 0)
		{
			das_war_ein_treffer = true; cout << "Schuss hat getroffen." << endl;
		}
		else if (ii == 2)
		{
			das_war_ein_treffer = true; cout << "Schuss hat getroffen." << endl;
		}
		else if (ii == 3)
		{
			das_war_ein_treffer = true; cout << "Schuss hat getroffen." << endl;
		}
		else
		{
			das_war_ein_treffer = false; cout << "Schuss ging daneben." << endl;
		}
		;
	}

*/