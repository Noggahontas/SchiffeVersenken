#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
using namespace std;


bool Player::ShotOn(Position Shot)
{
	// Schuss von Gegner auf Koordinaten Shot	
	// �ndert Last3ShotsOfOpponent
	// Gibt zur�ck ob ein Schiff getroffen wurde: 1 = getroffen, 0= nicht getroffen

	Last3ShotsOfOpponent.insert(Last3ShotsOfOpponent.begin(), Shot);	//An Position 0 neuen Schuss des Gegners einf�gen (Iterator auf Position 0 wird �bergeben)
																		//Nun sind es 4 Element!
	Last3ShotsOfOpponent.pop_back();									//Letztes Element l�schen -> Es sind wieder die letzten 3 Sch�sse gespeichert

	bool Hit;							// Angabe ob ein Schiff getroffen wurde
	int i = 0;
	do									// Ausf�hren bis ein getroffenes Schiff gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
	{
		Hit = Ships[i].IsHit(Shot);		// Funktion ISHit gibt zur�ck ob dieses Schiff getroffen wurde
		i++;
	} while ( (i < 10) & (Hit != 1) );	

	return Hit;			// R�ckgabe ob ein Schiff getroffen wurde
}







bool Player::Move(int ShipNumber, MoveDirection Direction)
{
	// �bergabe welches Schiff bewegt werden soll. Nummer Schiff = Index i aus Array Ships[i] 
	// �bergabe Richtung, in die bewegt werden soll: Forward oder Backward. ein Schiff kann nur in L�ngsrichtung bewegt werden
	// Kollisionsabfrage ob Bewegen m�glich, wenn ja:
	// �ndert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
	// R�ckgabe ob Bewegen m�glich/erfolgreich war. Geklappt=1, Nicht geklappt=0

	bool MoveSuccess = 1;			// Angabe ob Bewegen m�glich war

	Position CriticalCoordinates;	// Koordinaten, die Schiff nach dem Bewegen belegen w�rde
									// F�r diese muss gepr�ft werden ob das m�glich ist -> Kollision/ Au�erhalb Spielfeld

	bool Collision;					// Angabe ob es durch Bewegen eine Kollision mit einem Schiff g�be

	bool Hit;						// Angabe ob es durch Bewegen eine Kollision mit einem Feld geben w�rde, das in den letzten 3 Runden abgeschossen wurde
		
	bool InsideBattlefield;			//Angabe ob nach Bewegen noch innerhalb von Schlachtfeld w�re


	if (Direction == MoveDirection::Forward)		// Wenn Schiff sich vorw�rts bewegen soll 
	{	
		if (Ships[ShipNumber].Orientation == Direction::Right)	// Wenn Schiff nach rechts ausgerichtet ist (von StartPos aus)
		{					
			// x-Koordinate wird durch Bewegen um 1 erh�ht -> Koordinaten, die gepr�ft werden m�ssen:
			// aktuelle Startposition x-Koord. + (L�nge Schiff-1) = x-Koordinate von aktuellem letzten Feld des Schiffs 
			// aktuelles letztes Feld Schiff + um 1 Bewegen = neue x-Koordinate, die Schiff durch Bewegen belegen w�rde
			// an y-Koordinate �ndert sich nichts
			CriticalCoordinates = { (Ships[ShipNumber].StartPos.x + (Ships[ShipNumber].Length - 1) + 1 ) , Ships[ShipNumber].StartPos.y };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = ( CriticalCoordinates.x <= 9);	

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausf�hren f�r alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zur�ck ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, d�rfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Pr�fung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tats�chlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.x++;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht m�glich
			}

		}
		else if (Ships[ShipNumber].Orientation == Direction::Down)		// Wenn Schiff nach unten ausgerichtet ist (von StartPos aus)
		{
			// y-Koordinate wird durch Bewegen um 1 erh�ht -> Koordinaten, die gepr�ft werden m�ssen:
			// aktuelle Startposition y-Koord. + (L�nge Schiff-1) = y-Koordinate von aktuellem letztes Feld des Schiff 
			// aktuelle letzte y-Koordinate Schiff + um 1 Bewegen = neue y-Koordinate, die Schiff durch Bewegen belegen w�rde
			// an x-Koordinate �ndert sich nichts
			CriticalCoordinates = {  Ships[ShipNumber].StartPos.x , Ships[ShipNumber].StartPos.y + (Ships[ShipNumber].Length - 1) + 1 };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = (CriticalCoordinates.y <= 9);

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausf�hren f�r alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zur�ck ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, d�rfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Pr�fung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tats�chlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.y++;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht m�glich
			}
		}	
	}
	else if (Direction == MoveDirection::Backward)	// Wenn Schiff sich r�ckw�rts bewegen soll
	{
		if (Ships[ShipNumber].Orientation == Direction::Right)	// Wenn Schiff nach rechts ausgerichtet ist (von StartPos aus)
		{
			// x-Koordinate wird durch Bewegen um 1 erniedrigt -> Koordinaten, die gepr�ft werden m�ssen:
			// x-Koordinate von aktuellem ersten Feld des Schiffs  - um 1 Bewegen = neue x-Koordinate, die Schiff durch Bewegen belegen w�rde
			// an y-Koordinate �ndert sich nichts
			CriticalCoordinates = { Ships[ShipNumber].StartPos.x - 1 , Ships[ShipNumber].StartPos.y };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = (CriticalCoordinates.x >= 0);

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausf�hren f�r alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zur�ck ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, d�rfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Pr�fung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tats�chlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.x--;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht m�glich
			}

		}
		else if (Ships[ShipNumber].Orientation == Direction::Down)		// Wenn Schiff nach unten ausgerichtet ist (von StartPos aus)
		{
			// y-Koordinate wird durch Bewegen um 1 erniedrigt -> Koordinaten, die gepr�ft werden m�ssen:
			// aktuelle Startposition y-Koord. - 1 durch Bewegen = neue y-Koordinate, die Schiff durch Bewegen belegen w�rde
			// an x-Koordinate �ndert sich nichts
			CriticalCoordinates = { Ships[ShipNumber].StartPos.x, Ships[ShipNumber].StartPos.y - 1 };

			// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
			InsideBattlefield = (CriticalCoordinates.y >= 0);

			// Check, ob auf neuen Koordinaten durch Bewegen schon ein Schiff sitzt
			int i = 0;
			do				// Ausf�hren f�r alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				Collision = Ships[i].AreYouThere(CriticalCoordinates);	// AreYouThere() gibt zur�ck ob das Schiff auf diesem Feld sitzt
				i++;
			} while ((i < 10) & (Collision != 1));

			//Check, ob auf neue Koordinaten durch Bewegen in den letzten 3 Runden ein Schuss gefallen ist
			//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, d�rfen von eigenen Schiffen nicht belegt werden
			Hit = 0;
			for (int i = 0; i < 3; i++)
			{
				if ((Last3ShotsOfOpponent.at(i).x == CriticalCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == CriticalCoordinates.y))
				{
					Hit = 1;
				}
			}

			// Wenn bei Pr�fung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tats�chlich bewegt werden
			// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
			if (!Collision & !Hit & InsideBattlefield)
			{
				Ships[ShipNumber].StartPos.y--;
				return 1;						// Bewegen erfolgreich
			}
			else
			{
				return 0;						// Bewegen nicht m�glich
			}
		}
	}

}









Player::Player() {
	 // Konstruktor 
	 // St��t Konstruktor f�r jedes Schiff an
	 // legt Gr��e von Last3ShotsOfOpponent fest und initialisiert mit NULL
	 // W�hlt zuf�llig AttackStrategy und DefenseStrategy aus

	 //Bei Player P1
	// Einlesen der Initialisierungswerte der Schiffe aus Textdatei
	// Eigentlich mit Lexikalischer Analyse:
	//...
	// Vorl�ufige L�sung: Direktes, festes Initialisieren; Korrekte L�sung kommt noch

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

	// Dies soll sp�ter zuf�llig passieren
	AttackStrategy = 1;
	DefenseStrategy = 1;

	Last3ShotsOfOpponent.resize(3, { NULL, NULL });	// Noch keine Sch�sse abgefeuert -> NULL




// Ohne lexikalische Analyse - so war es nicht gedacht
// Folgende Probleme hier: Letztes Schiff wird falsch initialisiert und ein NULL Problem -> Mystery
// Einlesen aus Textdatei, um Schiffe zu initialisieren

	//FILE* File;
	//char *Element;						//separiertes Element aus einer Zeile
	//char* Filename = "SetShips.txt";
	//const int Bufferlen = 20;
	//char Buffer[Bufferlen];				// Puffer zum Einlesen einer Zeile

	//int ShipNumber = 0;		// Zum Z�hlen der Zeilen. Zeilen werden Schiffen zugeordnet


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
	//	{							//Quick and Dirt L�sung	// - 48, weil die Zhalen aus Textdatei werden als ASCII Zeichen zur�ckgegeben int 0 -> 48 in ASCII
	//		Ships[ShipNumber].Length = *Element - 48 ;		// In Textdatei steht die L�nge in erster Spalte
	//		
	//		Element = strtok(NULL, "\n \t");			//n�chstes Elemente aus Buffer separieren
	//		Ships[ShipNumber].StartPos.x = *Element - 48;	// In Textdatei steht die x-Koordinate der Startposition in der zweiten Spalte

	//		Element = strtok(NULL, "\n \t");			//n�chstes Elemente aus Buffer separieren
	//		Ships[ShipNumber].StartPos.y = *Element - 48;	// In Textdatei steht y-Koordinate der Startposition in der ditten Spalte

	//		Element = strtok(NULL, "\n \t");			//n�chstes Elemente aus Buffer separieren
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

	//	ShipNumber++;	// n�chste Zeile wird geholt, gilt f�r n�chstes Schiff
	//}

}







