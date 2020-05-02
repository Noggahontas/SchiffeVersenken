#include "stdafx.h"
#include "Ship.h"

bool Ship::IsHit(Position Shot)
{	// Im Übergabeparameter Shot (Struct) werden die Koordinaten des Schusses (vom Gegner) übergeben
	// Gibt an ob Schiff getroffen wurde: Rückgabe 1=Schiff wurde gehittet; 0=nicht geghittet
	//ändert bei einem Hit Status-Vector
	// Aufruf Funktion StillAlive

	bool Hit = 0; // Zwischenspeichern der Feststellung, dass Schiff getroffen wurde
	if (Direction == Right)	//Schiff von Startposition aus gesehen nach rechts ausgerichtet (x-Richtung)
	{
		for (int i = 0; i < Length; i++)
		{
			if ((StartPos.x + i == Shot.x) & (StartPos.y == Shot.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes überein
			{
				Status.at(i) = 1;	//Feld des Schiffes wird als getroffen markiert: 1=getroffen
				Hit = 1;			// Schiff wurde getroffen
			}
		}
	}
	else if (Direction == Down)
	{
		for (int i = 0; i < Length; i++)
		{
			if ((StartPos.x == Shot.x) & (StartPos.y + i == Shot.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes überein
			{
				Status.at(i) = 1;	//Feld des Schiffes wird als getroffen markiert: 1=getroffen
				Hit = 1;			// Schiff wurde getroffen
			}
		}
	}

	this->StillAlive(); // Aufruf der Funktion StillAlive für dieses Schiff
	return Hit;	
}

void Ship::StillAlive()
{
	// Prüft anhand des Statusvektors Status ob das Schiff schon an allen Feldern getroffen wurde, also ob es schon versenkt wurde
	// Wenn es versenkt wurde, ändert es die Klassenvariable Sunk zu 1

	vector<bool> Check(Length); //um zu checken, ob alle Felder des Schiffs getroffen wurden

	for (int i = 0; i < Length; i++)
	{
		if (Status.at(i) == 0) { Sunk = 0; 	return; }	// Sobald ein Feld des Schiffes noch nicht getroffen wurde (=0), ist es noch nicht versenkt worden
	
	}

	Sunk = 1;	// Wenn die Schleife voll durchlaufen wird, ohne dass die Fkt. mit return vorzeitig beendet wird, ist das Schiff versenkt worden
}