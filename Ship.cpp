#include "stdafx.h"
#include "Ship.h"
using namespace std;



bool Ship::IsHit(Position Shot)
{	// Im Übergabeparameter Shot (Struct) werden die Koordinaten des Schusses (vom Gegner) übergeben
	// Gibt an ob Schiff getroffen wurde: Rückgabe 1=Schiff wurde gehittet; 0=nicht geghittet
	// ändert bei einem Hit den Status-Vector
	// Aufruf Funktion StillAlive

	bool Hit = 0;		// Zwischenspeichern der Feststellung, dass Schiff getroffen wurde

	if (Orientation == Direction::Right)	// Schiff ist von Startposition aus gesehen nach rechts ausgerichtet (x-Richtung)
	{
		for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
		{	// Nach rechts ausgerichtet -> x-Koordinate muss erhöht werden
			if ((StartPos.x + i == Shot.x) & (StartPos.y == Shot.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes überein
			{
				if (Status.at(i) == 0)	// Nur wenn dieses Schiffsfeld noch nie getroffen wurde zählt der Schuss als Treffer
				{
					Status.at(i) = 1;	// Feld des Schiffes wird als getroffen markiert: 1=getroffen
					Hit = 1;			// Schiff wurde getroffen
				}
			}
		}
	}
	else if (Orientation == Direction::Down) // Schiff von Startposition aus gesehen nach unten ausgerichtet (y-Richtung)
	{	// Nach unten ausgerichtet -> y-Koordinate muss erhöht werden
		for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
		{
			if ((StartPos.x == Shot.x) & (StartPos.y + i == Shot.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes überein
			{
				if (Status.at(i) == 0)	// Nur wenn dieses Schiffsfeld noch nie getroffen wurde zählt der Schuss als Treffer
				{
					Status.at(i) = 1;	// Feld des Schiffes wird als getroffen markiert: 1=getroffen
					Hit = 1;			// Schiff wurde getroffen
				}
			}
		}
	}

	this->StillAlive();					// Aufruf der Funktion StillAlive für dieses Schiff
	return Hit;	
}







void Ship::StillAlive()
{	// Ändert Variable Sunk wenn nötig
	// Prüft anhand des Statusvektors Status ob das Schiff schon an allen Feldern getroffen wurde, also ob es schon versenkt wurde
	// Wenn es versenkt wurde, ändert es die Klassenvariable Sunk zu 1

	for (int i = 0; i < Length; i++)
	{
		if (Status.at(i) == 0) { Sunk = 0; 	return; }	// Sobald ein einziges Feld des Schiffes noch nicht getroffen wurde (=0), ist Schiff noch nicht versenkt worden

	}

	Sunk = 1;	// Wenn die Schleife voll durchlaufen wird, ohne dass die Fkt. mit return vorzeitig beendet wird, ist das Schiff versenkt worden
}






bool Ship::AreYouThere(Position CriticalCoordinates)
{
	// Übergabe: Koordinaten, von denen gecheckt werden soll ob Schiff darauf steht
	// Rückgabe: Befindet sich an diesen Koordinaten das Schiff:  1=ja, 0=nein

	bool Occupied = 0;		// Zwischenspeichern der Feststellung, ob Schiff auf diesem Feld sitzt

	if(Sunk == false)		// Nur wenn Schiff noch nicht versenkt wurde, belegt es ein Feld. Wenn es versenkt wurde, kann ein anderes Schiff diese Felder belegen
	{ 
		if (Orientation == Direction::Right)	// Schiff von Startposition aus gesehen nach rechts ausgerichtet (x-Richtung)
		{	
			for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
			{		// Nach rechts ausgerichtet -> x-Koordinate muss erhöht werden
					if ((StartPos.x + i == CriticalCoordinates.x) & (StartPos.y == CriticalCoordinates.y))	// Koordinaten stimmen mit der Position des Schiff-Feldes überein
					{
						Occupied = 1;			// Schiff sitzt auf Feld
					}
			}
		}
		else if (Orientation == Direction::Down) //Schiff von Startposition aus gesehen nach unten ausgerichtet (y-Richtung)
		{
			for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
			{	// Nach rechts ausgerichtet -> y-Koordinate muss erhöht werden
				if ((StartPos.x == CriticalCoordinates.x) & (StartPos.y + i == CriticalCoordinates.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes überein
				{
					Occupied = 1;			// Schiff sitzt auf Feld
				}
			}
		}
	}

	return Occupied;	// Rückgabe ob übergebene Koordinaten von einem Schiff besetzt sind
}





Ship::Ship()
{
	Length = NULL;
	StartPos = { NULL, NULL };
	Orientation = Direction::Down;	// NULL nicht möglich, da enum class
	Sunk = NULL;
	Sunk = 0;						// NULL nicht möglich, da bool
}