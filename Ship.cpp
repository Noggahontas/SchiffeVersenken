#include "stdafx.h"
#include "Ship.h"
using namespace std;



bool Ship::IsHit(Position Shot)
{	// Im �bergabeparameter Shot (Struct) werden die Koordinaten des Schusses (vom Gegner) �bergeben
	// Gibt an ob Schiff getroffen wurde: R�ckgabe 1=Schiff wurde gehittet; 0=nicht geghittet
	// �ndert bei einem Hit den Status-Vector
	// Aufruf Funktion StillAlive

	bool Hit = 0;		// Zwischenspeichern der Feststellung, dass Schiff getroffen wurde

	if (Orientation == Direction::Right)	// Schiff ist von Startposition aus gesehen nach rechts ausgerichtet (x-Richtung)
	{
		for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
		{	// Nach rechts ausgerichtet -> x-Koordinate muss erh�ht werden
			if ((StartPos.x + i == Shot.x) & (StartPos.y == Shot.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes �berein
			{
				if (Status.at(i) == 0)	// Nur wenn dieses Schiffsfeld noch nie getroffen wurde z�hlt der Schuss als Treffer
				{
					Status.at(i) = 1;	// Feld des Schiffes wird als getroffen markiert: 1=getroffen
					Hit = 1;			// Schiff wurde getroffen
				}
			}
		}
	}
	else if (Orientation == Direction::Down) // Schiff von Startposition aus gesehen nach unten ausgerichtet (y-Richtung)
	{	// Nach unten ausgerichtet -> y-Koordinate muss erh�ht werden
		for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
		{
			if ((StartPos.x == Shot.x) & (StartPos.y + i == Shot.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes �berein
			{
				if (Status.at(i) == 0)	// Nur wenn dieses Schiffsfeld noch nie getroffen wurde z�hlt der Schuss als Treffer
				{
					Status.at(i) = 1;	// Feld des Schiffes wird als getroffen markiert: 1=getroffen
					Hit = 1;			// Schiff wurde getroffen
				}
			}
		}
	}

	this->StillAlive();					// Aufruf der Funktion StillAlive f�r dieses Schiff
	return Hit;	
}







void Ship::StillAlive()
{	// �ndert Variable Sunk wenn n�tig
	// Pr�ft anhand des Statusvektors Status ob das Schiff schon an allen Feldern getroffen wurde, also ob es schon versenkt wurde
	// Wenn es versenkt wurde, �ndert es die Klassenvariable Sunk zu 1

	for (int i = 0; i < Length; i++)
	{
		if (Status.at(i) == 0) { Sunk = 0; 	return; }	// Sobald ein einziges Feld des Schiffes noch nicht getroffen wurde (=0), ist Schiff noch nicht versenkt worden

	}

	Sunk = 1;	// Wenn die Schleife voll durchlaufen wird, ohne dass die Fkt. mit return vorzeitig beendet wird, ist das Schiff versenkt worden
}






bool Ship::AreYouThere(Position CriticalCoordinates)
{
	// �bergabe: Koordinaten, von denen gecheckt werden soll ob Schiff darauf steht
	// R�ckgabe: Befindet sich an diesen Koordinaten das Schiff:  1=ja, 0=nein

	bool Occupied = 0;		// Zwischenspeichern der Feststellung, ob Schiff auf diesem Feld sitzt

	if(Sunk == false)		// Nur wenn Schiff noch nicht versenkt wurde, belegt es ein Feld. Wenn es versenkt wurde, kann ein anderes Schiff diese Felder belegen
	{ 
		if (Orientation == Direction::Right)	// Schiff von Startposition aus gesehen nach rechts ausgerichtet (x-Richtung)
		{	
			for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
			{		// Nach rechts ausgerichtet -> x-Koordinate muss erh�ht werden
					if ((StartPos.x + i == CriticalCoordinates.x) & (StartPos.y == CriticalCoordinates.y))	// Koordinaten stimmen mit der Position des Schiff-Feldes �berein
					{
						Occupied = 1;			// Schiff sitzt auf Feld
					}
			}
		}
		else if (Orientation == Direction::Down) //Schiff von Startposition aus gesehen nach unten ausgerichtet (y-Richtung)
		{
			for (int i = 0; i < Length; i++)	// Durchlauf aller Koordinaten, die das Schiff belegt
			{	// Nach rechts ausgerichtet -> y-Koordinate muss erh�ht werden
				if ((StartPos.x == CriticalCoordinates.x) & (StartPos.y + i == CriticalCoordinates.y))	//Koordinaten des Schusses stimmen mit der Position des Schiff-Feldes �berein
				{
					Occupied = 1;			// Schiff sitzt auf Feld
				}
			}
		}
	}

	return Occupied;	// R�ckgabe ob �bergebene Koordinaten von einem Schiff besetzt sind
}





Ship::Ship()
{
	Length = NULL;
	StartPos = { NULL, NULL };
	Orientation = Direction::Down;	// NULL nicht m�glich, da enum class
	Sunk = NULL;
	Sunk = 0;						// NULL nicht m�glich, da bool
}