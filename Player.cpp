#pragma once
#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "AttackStrategy1.h"
#include "AttackStrategy2.h"
#include "AttackStrategy3.h"
using namespace std;


bool Player::ShotOn(Position Shot)
{
	// Schuss von Gegner auf Koordinaten Shot	
	// ändert Last3ShotsOfOpponent
	// Gibt zurück ob ein Schiff getroffen wurde: 1 = getroffen, 0= nicht getroffen

	Last3ShotsOfOpponent.insert(Last3ShotsOfOpponent.begin(), Shot);	//An Position 0 neuen Schuss des Gegners einfügen (Iterator auf Position 0 wird übergeben)
																		//Nun sind es 4 Element!
	Last3ShotsOfOpponent.pop_back();									//Letztes Element löschen -> Es sind wieder die letzten 3 Schüsse gespeichert

	bool Hit;							// Angabe ob ein Schiff getroffen wurde
	int i = 0;
	do									// Ausführen bis ein getroffenes Schiff gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
	{
		Hit = Ships[i].IsHit(Shot);		// Funktion ISHit gibt zurück ob dieses Schiff getroffen wurde
		i++;
	} while ( (i < 10) & (Hit != 1) );	

	CheckIfLost();		// Ruft Funktion CheckIfLost() für diesen Spieler auf um die Variable Lost ggf. zu aktualisieren
	return Hit;			// Rückgabe ob ein Schiff getroffen wurde
}






void Player::CheckIfLost()
{
	// Prüft ob alle Schiffe eines Spielers versenkt wurden und aktualisiert ggf. Variable Lost

	for (int i = 0; i < 10; i++)
	{
		if (Ships[i].Sunk == 0) { return; }	// Sobald ein einziges Schiff noch nicht versenkt wurde (=0), hat Spieler noch nicht verloren

	}

	Lost = 1;	// Wenn die Schleife voll durchlaufen wird, ohne dass die Fkt. mit return vorzeitig beendet wird, hat Spieler verloren
}






bool Player::Move(int ShipNumber, MoveDirection Direction)
{
	// Übergabe welches Schiff bewegt werden soll. Nummer Schiff = Index i aus Array Ships[i] 
	// Übergabe Richtung, in die bewegt werden soll: Forward oder Backward. ein Schiff kann nur in Längsrichtung bewegt werden
	// Kollisionsabfrage ob Bewegen möglich, wenn ja:
	// Ändert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
	// Rückgabe ob Bewegen möglich/erfolgreich war. Geklappt=1, Nicht geklappt=0

	bool MoveSuccess = 1;			// Angabe ob Bewegen möglich war

	Position CriticalCoordinates;	// Koordinaten, die Schiff nach dem Bewegen belegen würde
									// Für diese muss geprüft werden ob das möglich ist -> Kollision/ Außerhalb Spielfeld

	bool Collision;					// Angabe ob es durch Bewegen eine Kollision mit einem Schiff gäbe

	bool Hit;						// Angabe ob es durch Bewegen eine Kollision mit einem Feld geben würde, das in den letzten 3 Runden abgeschossen wurde
		
	bool InsideBattlefield;			//Angabe ob nach Bewegen noch innerhalb von Schlachtfeld wäre


	if (Direction == MoveDirection::Forward)		// Wenn Schiff sich vorwärts bewegen soll 
	{	
		if (Ships[ShipNumber].Orientation == Direction::Right)	// Wenn Schiff nach rechts ausgerichtet ist (von StartPos aus)
		{					
			// x-Koordinate wird durch Bewegen um 1 erhöht -> Koordinaten, die geprüft werden müssen:
			// aktuelle Startposition x-Koord. + (Länge Schiff-1) = x-Koordinate von aktuellem letzten Feld des Schiffs 
			// aktuelles letztes Feld Schiff + um 1 Bewegen = neue x-Koordinate, die Schiff durch Bewegen belegen würde
			// an y-Koordinate ändert sich nichts
			CriticalCoordinates = { (Ships[ShipNumber].StartPos.x + (Ships[ShipNumber].Length - 1) + 1 ) , Ships[ShipNumber].StartPos.y };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = ( CriticalCoordinates.x <= 9);	

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausführen für alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zurück ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, dürfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Prüfung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tatsächlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.x++;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht möglich
			}

		}
		else if (Ships[ShipNumber].Orientation == Direction::Down)		// Wenn Schiff nach unten ausgerichtet ist (von StartPos aus)
		{
			// y-Koordinate wird durch Bewegen um 1 erhöht -> Koordinaten, die geprüft werden müssen:
			// aktuelle Startposition y-Koord. + (Länge Schiff-1) = y-Koordinate von aktuellem letztes Feld des Schiff 
			// aktuelle letzte y-Koordinate Schiff + um 1 Bewegen = neue y-Koordinate, die Schiff durch Bewegen belegen würde
			// an x-Koordinate ändert sich nichts
			CriticalCoordinates = {  Ships[ShipNumber].StartPos.x , Ships[ShipNumber].StartPos.y + (Ships[ShipNumber].Length - 1) + 1 };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = (CriticalCoordinates.y <= 9);

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausführen für alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zurück ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, dürfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Prüfung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tatsächlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.y++;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht möglich
			}
		}	
	}
	else if (Direction == MoveDirection::Backward)	// Wenn Schiff sich rückwärts bewegen soll
	{
		if (Ships[ShipNumber].Orientation == Direction::Right)	// Wenn Schiff nach rechts ausgerichtet ist (von StartPos aus)
		{
			// x-Koordinate wird durch Bewegen um 1 erniedrigt -> Koordinaten, die geprüft werden müssen:
			// x-Koordinate von aktuellem ersten Feld des Schiffs  - um 1 Bewegen = neue x-Koordinate, die Schiff durch Bewegen belegen würde
			// an y-Koordinate ändert sich nichts
			CriticalCoordinates = { Ships[ShipNumber].StartPos.x - 1 , Ships[ShipNumber].StartPos.y };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = (CriticalCoordinates.x >= 0);

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausführen für alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zurück ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, dürfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Prüfung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tatsächlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.x--;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht möglich
			}

		}
		else if (Ships[ShipNumber].Orientation == Direction::Down)		// Wenn Schiff nach unten ausgerichtet ist (von StartPos aus)
		{
			// y-Koordinate wird durch Bewegen um 1 erniedrigt -> Koordinaten, die geprüft werden müssen:
			// aktuelle Startposition y-Koord. - 1 durch Bewegen = neue y-Koordinate, die Schiff durch Bewegen belegen würde
			// an x-Koordinate ändert sich nichts
			CriticalCoordinates = { Ships[ShipNumber].StartPos.x, Ships[ShipNumber].StartPos.y - 1 };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = (CriticalCoordinates.y >= 0);

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausführen für alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zurück ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, dürfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Prüfung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tatsächlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.y--;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht möglich
			}
		}
	}
	return 0 ;	// Fehler ist aufgetreten
}





Position Player::FindAttackShot()
{
	// Gibt je nach gewählter Angriffsstrategie (AttackStrategy) eines Spielers Koordinaten zurück, auf die geschossen werden soll

	switch (AttackStrategy)
	{
	case 1:
		//return AttackStrategy1(&Last3ShotsOfOpponent);
		return { 1,1 };

	case 2:
		//return AttackStrategy2(&Shot);		//zweiter Übergabeparameter muss nur mit übergeben werden
		return { 2,2 };

	case 3:
		//return AttackStrategy3(&Last3ShotsOfOpponent.at(0));
		return { 3,3 };

	default:
		return { -1, -1 };
	}

}

void Player::DefensiveAction()
{
	// Ermittelt je nach gewählter Angriffsstrategie einen Verteidigungsmove: 
	// Bewegen oder Drehen und welches Schiff, oder auch gar nichts
	// Ruft ggf. Funktion Turn oder Move auf 


}



Player::Player() {
	 // Konstruktor 
	 // Stößt Konstruktor für jedes Schiff an
	 // legt Größe von Last3ShotsOfOpponent fest und initialisiert mit NULL
	 // Wählt zufällig AttackStrategy und DefenseStrategy aus

	 //Bei Player P1
	// Einlesen der Initialisierungswerte der Schiffe aus Textdatei
	// Eigentlich mit Lexikalischer Analyse:
	//...
	// Vorläufige Lösung: Direktes, festes Initialisieren; Korrekte Lösung kommt noch

	Ships[0].Length = 5;
	Ships[0].StartPos = { 0,0 };
	Ships[0].Orientation = Direction::Down;
	Ships[0].Status.resize(Ships[0].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[0].Sunk = 0;							// Noch keine Treffer, noch nicht versenkt

	Ships[1].Length = 4;
	Ships[1].StartPos = { 4,2 };
	Ships[1].Orientation = Direction::Right;
	Ships[1].Status.resize(Ships[1].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[1].Sunk = 0;

	Ships[2].Length = 4;
	Ships[2].StartPos = { 8,6 };
	Ships[2].Orientation = Direction::Down;
	Ships[2].Status.resize(Ships[2].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[2].Sunk = 0;

	Ships[3].Length = 3;
	Ships[3].StartPos = { 0,7 };
	Ships[3].Orientation = Direction::Right;
	Ships[3].Status.resize(Ships[3].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[3].Sunk = 0;

	Ships[4].Length = 3;
	Ships[4].StartPos = { 2,3 };
	Ships[4].Orientation = Direction::Down;
	Ships[4].Status.resize(Ships[4].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[4].Sunk = 0;

	Ships[5].Length = 3;
	Ships[5].StartPos = { 5,4 };
	Ships[5].Orientation = Direction::Down;
	Ships[5].Status.resize(Ships[5].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[5].Sunk = 0;

	Ships[6].Length = 2;
	Ships[6].StartPos = { 3,0 };
	Ships[6].Orientation = Direction::Right;
	Ships[6].Status.resize(Ships[6].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[6].Sunk = 0;

	Ships[7].Length = 2;
	Ships[7].StartPos = { 9,0 };
	Ships[7].Orientation = Direction::Down;
	Ships[7].Status.resize(Ships[7].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[7].Sunk = 0;

	Ships[8].Length = 2;
	Ships[8].StartPos = { 9,3 };
	Ships[8].Orientation = Direction::Down;
	Ships[8].Status.resize(Ships[8].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[8].Sunk = 0;

	Ships[9].Length = 2;
	Ships[9].StartPos = { 3,9 };
	Ships[9].Orientation = Direction::Right;
	Ships[9].Status.resize(Ships[9].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	Ships[9].Sunk = 0;

	// Dies soll später zufällig passieren ODER vom Nutzer geählt werden

	// Spieler 1 und Spieler 2 dürfen NICHT DIESELBE ANGRIFFSSTRAGTEGIE haben!!!!!!!  -> geht das wenn es zufällig ist?? -> testen vlt  mit festen Werten
	// Lösungsansatz: Mit ermitteltem Zufallswert in "main", dann ´nicht mit Standartkonstruktorm sondern einem dem der Wert übergeben wird!
	AttackStrategy = 1;
	DefenseStrategy = 1;

	Last3ShotsOfOpponent.resize(3, { NULL, NULL });	// Noch keine Schüsse abgefeuert -> NULL

	Lost = 0;




// Ohne lexikalische Analyse - so war es nicht gedacht
// Folgende Probleme hier: Letztes Schiff wird falsch initialisiert und ein NULL Problem -> Mystery
// Einlesen aus Textdatei, um Schiffe zu initialisieren

	//FILE* File;
	//char *Element;						//separiertes Element aus einer Zeile
	//char* Filename = "SetShips.txt";
	//const int Bufferlen = 20;
	//char Buffer[Bufferlen];				// Puffer zum Einlesen einer Zeile

	//int ShipNumber = 0;		// Zum Zählen der Zeilen. Zeilen werden Schiffen zugeordnet


	//File = fopen(Filename, "r");

	//if (File == NULL)
	//{
	//	printf("Cannot open file %s", Filename);
	//	return;							// Springt das auch aus dem Konstruktor?
	//}

	//while (!feof(File))
	//{
	//	fgets(Buffer, Bufferlen, File);			// eine Zeile einlesen

	//	Element = strtok(Buffer, "\n \t");		// erstes Element ohne Trennzeichen aus Buffer separieren

	//	while (Element != NULL)					// Bis der Buffer ganz durchlaufen wurde			
	//	{							//Quick and Dirt Lösung	// - 48, weil die Zhalen aus Textdatei werden als ASCII Zeichen zurückgegeben int 0 -> 48 in ASCII
	//		Ships[ShipNumber].Length = *Element - 48 ;		// In Textdatei steht die Länge in erster Spalte
	//		
	//		Element = strtok(NULL, "\n \t");			//nächstes Elemente aus Buffer separieren
	//		Ships[ShipNumber].StartPos.x = *Element - 48;	// In Textdatei steht die x-Koordinate der Startposition in der zweiten Spalte

	//		Element = strtok(NULL, "\n \t");			//nächstes Elemente aus Buffer separieren
	//		Ships[ShipNumber].StartPos.y = *Element - 48;	// In Textdatei steht y-Koordinate der Startposition in der ditten Spalte

	//		Element = strtok(NULL, "\n \t");			//nächstes Elemente aus Buffer separieren
	//		if((*Element - 48) == 0)							// In Textdatei steht in letzter Spalte die Ausrichtung
	//		{
	//			Ships[ShipNumber].Orientation = Direction::Right;	
	//		}
	//		else if ((*Element -48) == 1)
	//		{
	//			Ships[ShipNumber].Orientation = Direction::Down;	
	//		}
	//		
	//		Element = strtok(NULL, "\n \t");

	//	}

	//	ShipNumber++;	// nächste Zeile wird geholt, gilt für nächstes Schiff
	//}

}







