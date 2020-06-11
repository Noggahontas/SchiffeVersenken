#pragma once
#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "AttackStrategy1.h"
#include "AttackStrategy2.h"
#include "AttackStrategy3.h"
#include "AttackStrategy4.h"
#include "DefenseStrategy1.h"
#include <time.h>	// Für Generierung Zufallszahlen
using namespace std;
#include "PlayerLexan.h"


AttackResult Player::ShotOn(Position Shot)
{
	// Schuss von Gegner auf Koordinaten Shot	
	// ändert Last3ShotsOfOpponent
	// Rückgabe als Strukt 
	// Gibt zurück ob ein Schiff getroffen wurde: Hit=1= getroffen, Hit=0=nicht getroffen
	// Gibt zurück ob ein Schiff versenkt wurde: Sunk=1=versenkt, Sunk=0=nicht versenkt

	Last3ShotsOfOpponent.insert(Last3ShotsOfOpponent.begin(), Shot);	//An Position 0 neuen Schuss des Gegners einfügen (Iterator auf Position 0 wird übergeben)
																		//Nun sind es 4 Element!
	Last3ShotsOfOpponent.pop_back();									//Letztes Element löschen -> Es sind wieder die letzten 3 Schüsse gespeichert

	AttackResult Result;				// Result.Hit: Angabe ob ein Schiff getroffen wurde
	Result.Sunk = false;					// Angabe ob ein Schiff versenkt wurde. Wenn kein Schiff getroffen wurde Sunk = 0
	
	int i = 0;
	do									// Ausführen bis ein getroffenes Schiff gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
	{
		Result.Hit = Ships[i].IsHit(Shot);		// Funktion ISHit gibt zurück ob dieses Schiff getroffen wurde
		i++;
	} while ( (i < 10) & (Result.Hit != true) );	// in i steht jetzt (Nummer des Schiffes +1), das getroffen wurde. Wenn kein Schiff getroffen wurde i=10

	if (Result.Hit == true)
	{
		Result.Sunk = Ships[i-1].Sunk;
	}

	// Aktualisieren der "Mitzählvariablen" für einen Vergleich der Strategien
	if (Result.Hit == true)
	{
		HitShotsOfOpponent++;
	}
	else
	{
		MissedShotsOfOpponent++;
	}
	if (Result.Sunk == true)
	{
		SunkShipsByOpponent++;
	}


	CheckIfLost();			// Ruft Funktion CheckIfLost() für diesen Spieler auf um die Variable Lost ggf. zu aktualisieren
	return Result;			// Rückgabe ob ein Schiff getroffen wurde
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

	//bool MoveSuccess = 1;			// Angabe ob Bewegen möglich war

	Position CriticalCoordinates;	// Koordinaten, die Schiff nach dem Bewegen belegen würde
									// Für diese muss geprüft werden ob das möglich ist -> Kollision/ Außerhalb Spielfeld		

	bool Collision;					// Angabe ob es durch Bewegen eine Kollision mit einem Schiff gäbe

	bool Hit;						// Angabe ob es durch Bewegen eine Kollision mit einem Feld geben würde, das in den letzten 3 Runden abgeschossen wurde
		
	bool InsideBattlefield;			//Angabe ob nach Bewegen noch innerhalb von Schlachtfeld wäre

	// Abfrage ob das Schiff, das bewegt werden soll, schon einen Treffer kassiert hat -> getroffene Schiffe sind bewegungsunfähig
	for (int i = 0; i < Ships[ShipNumber].Length; i++)
	{
		if (Ships[ShipNumber].Status.at(i) == true) 
		{	
				// Sobald ein einziges Feld des Schiffes getroffen wurde (=1), ist Schiff mind. 1x getroffen -> bewegungsunfähig 
				return 0;	// da Schiff getroffen, kann nicht bewegt werden 
		}
	}

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
			if ( !Collision & !Hit & InsideBattlefield)
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
			if ( !Collision & !Hit & InsideBattlefield)
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





bool Player::Turn(int ShipNumber)
{
	// Übergabe welches Schiff gedreht werden soll. Nummer Schiff = Index i aus Array Ships[i] 
	// Übergabe Richtung, in die gedrecht werden soll nicht notwendig, da ein Schiff entsprechend seiner Ausrichtung(Right oder Down) nur in eine Richtung gedreht werden kann. (Festlegung Ausrichtung: nach links, nach oben gibt es nicht)
	// Kollisionsabfrage ob Drehen möglich, wenn ja:
	// Ändert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
	// Rückgabe ob Drehen möglich/erfolgreich war. Geklappt=1, Nicht geklappt=0

	Position CriticalStartCoordinates;	// StartKoordinaten, die Schiff nach dem Drehen belegen würde x---
										// Für diese und die weiteren Koordinaten, die durch Schifflänge und neue Ausrichtung (durch Drehen) belegt werden würden,
										// muss geprüft werden ob das möglich ist -> Kollision/ Außerhalb Spielfeld /Hit	

	Direction NewOrientation;			// Neue Ausrichtung des Schiffs nach dem Drehen

	bool Collision;						// Angabe ob es durch Bewegen eine Kollision mit einem Schiff gäbe

	bool Hit;							// Angabe ob es durch Bewegen eine Kollision mit einem Feld geben würde, das in den letzten 3 Runden abgeschossen wurde

	bool InsideBattlefield;				//Angabe ob nach Bewegen noch innerhalb von Schlachtfeld wäre


	// Abfrage ob das Schiff, das bewegt werden soll, schon einen Treffer kassiert hat -> getroffene Schiffe sind bewegungsunfähig
	for (int i = 0; i < Ships[ShipNumber].Length; i++)
	{
		if (Ships[ShipNumber].Status.at(i) == true)
		{
			// Sobald ein einziges Feld des Schiffes getroffen wurde (=1), ist Schiff mind. 1x getroffen -> bewegungsunfähig 
			return 0;	// da Schiff getroffen, kann nicht gedreht werden 
		}
	}


	if (Ships[ShipNumber].Orientation == Direction::Right)	// Wenn das Schiff vor dem Drehen nach rechts ausgerichtet ist
	{
		NewOrientation = Direction::Down;					// Ein Schiff, das nach rechts ausgerichtet ist, kann nur im Uhrzeigersinn gedreht werden -> neue Ausrichtung nach unten

		// Neue Startposition nach dem Drehen bestimmen. In Abhängigkeit derLänge des Schiffs
		if (Ships[ShipNumber].Length == 2)		// Wenn Schiff die Länge 2 hat						
		{
			CriticalStartCoordinates = { Ships[ShipNumber].StartPos.x, Ships[ShipNumber].StartPos.y };	// dann bleibt die Startposition gleich, nur Ausrichtung ändert sich
		}
		else if ((Ships[ShipNumber].Length == 3) || (Ships[ShipNumber].Length == 4)) // Wenn Schiff die Länge 3 oder 4 hat
		{
			CriticalStartCoordinates = { (Ships[ShipNumber].StartPos.x + 1), (Ships[ShipNumber].StartPos.y - 1) };	// dann ändert sich Startposition: x+1, y-1
		}
		else if (Ships[ShipNumber].Length == 5) // Wenn Schiff die Länge 5 hat
		{
			CriticalStartCoordinates = { (Ships[ShipNumber].StartPos.x + 2), (Ships[ShipNumber].StartPos.y - 2) };	// dann ändert sich Startposition: x+2, y-2
		}
		else
		{
			CriticalStartCoordinates = { -1, -1 };
			cout << "Fehler in Funtktion Move() -> Abfrage Schiffslänge";
			return 0;
		}


		// Check, ob auf neuen Koordinaten durch Drehen schon ein Schiff sitzt
		Collision = false;
		int j = 0;
		do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden 
		{
			int i = 0;
			do				// Ausführen für alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{ 
				if( i != ShipNumber )						// Für das Schiff, das gedreht wird, soll nicht abgefragt werden, da es sich nicht selbst in die Quere kommt
				{ 
					Collision = Ships[i].AreYouThere({ CriticalStartCoordinates.x,(CriticalStartCoordinates.y + j) });	// AreYouThere() gibt zurück ob das Schiff auf diesem Feld sitzt
														// da neue Orientierung nach unten ist, sind Koordinaten zum Checken: {Start.x, Start.y+0},{Start.x, Start.y+1},...,{Start.x, Start.y+(Länge-1)}																	
				}
				i++;									// nächstes Schiff
			} while ( (i < 10) & (Collision == false) );

			j++;										// nächste Koordinate
		} while ((j < Ships[ShipNumber].Length) & (Collision == false) );
		



		//Check, ob auf neue Koordinaten durch Drehen in den letzten 3 Runden ein Schuss gefallen ist
		//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, dürfen von eigenen Schiffen nicht belegt werden
		Hit = 0;
		for (int i = 0; i < 3; i++)
		{
			j = 0;
			do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden 
			{
				if ( (Last3ShotsOfOpponent.at(i).x == CriticalStartCoordinates.x) & (Last3ShotsOfOpponent.at(i).y == (CriticalStartCoordinates.y + j)) )
				{
					Hit = 1;
				}
				j++;										// nächste Koordinate
			} while ((j < Ships[ShipNumber].Length) & (Hit != 1));
		}



		// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
		InsideBattlefield = true;
		j = 0;
		do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden
		{
			InsideBattlefield = ((CriticalStartCoordinates.y + j) <= 9) && ((CriticalStartCoordinates.y + j) >= 0);	// Beim Rechtsdrehen ist das Schiff in x-Richtung sicher immer innerhalb des Spielfeldes, weil
																					// Ausrichtung_aktuell = Right -> Ausrichtung_neu = Down. Nur die y-Koordinaten müssen gecheckt werden
			j++;																	// nächste Koordinate
		} while ((j < Ships[ShipNumber].Length) & (InsideBattlefield == true));
		



		// Wenn bei Prüfung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tatsächlich gedreht werden
		// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
		if (!Collision & !Hit & InsideBattlefield)
		{
			Ships[ShipNumber].StartPos = CriticalStartCoordinates;		// Neue Startposition übernehmen
			Ships[ShipNumber].Orientation = NewOrientation;				// Neue Ausrichtung übernehmen 
			return 1;						// Bewegen erfolgreich
		}
		else
		{
			return 0;						// Bewegen nicht möglich
		}

	}

	else if(Ships[ShipNumber].Orientation == Direction::Down)	// Wenn das Schiff vor dem Drehen nach unten ausgerichtet ist
	{
		NewOrientation = Direction::Right;						// Ein Schiff, das nach unten ausgerichtet ist, kann nur gegen den Uhrzeigersinn gedreht werden -> neue Ausrichtung nach rechts

		// Neue Startposition nach dem Drehen bestimmen. In Abhängigkeit derLänge des Schiffs
		if (Ships[ShipNumber].Length == 2)		// Wenn Schiff die Länge 2 hat						
		{
			CriticalStartCoordinates = { Ships[ShipNumber].StartPos.x, Ships[ShipNumber].StartPos.y };	// dann bleibt die Startposition gleich, nur Ausrichtung ändert sich
		}
		else if ((Ships[ShipNumber].Length == 3) || (Ships[ShipNumber].Length == 4)) // Wenn Schiff die Länge 3 oder 4 hat
		{
			CriticalStartCoordinates = { (Ships[ShipNumber].StartPos.x - 1), (Ships[ShipNumber].StartPos.y + 1) };	// dann ändert sich Startposition: x-1, y+1
		}
		else if (Ships[ShipNumber].Length == 5) // Wenn Schiff die Länge 5 hat
		{
			CriticalStartCoordinates = { (Ships[ShipNumber].StartPos.x - 2), (Ships[ShipNumber].StartPos.y + 2) };	// dann ändert sich Startposition: x-2, y+2
		}
		else
		{
			CriticalStartCoordinates = { -1, -1 };
			cout << "Fehler in Funtktion Move() -> Abfrage Schiffslänge";
			return 0;
		}


		// Check, ob auf neuen Koordinaten durch Drehen schon ein Schiff sitzt
		Collision = false;
		int j = 0;			// Zum Durchlaufen der Koordinaten
		do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden 
		{
			int i = 0;		// Zum Durchlaufen der Schiffe
			do				// Ausführen für alle Schiffe, bis ein Schiff auf CriticalCoordinates gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
			{
				if (i != ShipNumber)						// Für das Schiff, das gedreht wird, soll nicht abgefragt werden, da es sich nicht selbst in die Quere kommt
				{
					Collision = Ships[i].AreYouThere({ (CriticalStartCoordinates.x + j) ,CriticalStartCoordinates.y });	// AreYouThere() gibt zurück ob das Schiff auf diesem Feld sitzt
														// da neue Orientierung nach rechts ist, sind Koordinaten zum Checken: {Start.x+0, Start.y},{Start.x+1, Start.y},...,{Start.x+(Länge-1), Start.y}																	
				}
				i++;									// nächstes Schiff
			} while ((i < 10) & (Collision == false));

			j++;										// nächste Koordinate
		} while ((j < Ships[ShipNumber].Length) & (Collision == false));




		//Check, ob auf neue Koordinaten durch Drehen in den letzten 3 Runden ein Schuss gefallen ist
		//-> Felder, die innerhalb der letzten 3 Runden vom Gegner abgeschossen wurden, dürfen von eigenen Schiffen nicht belegt werden
		Hit = 0;
		for (int i = 0; i < 3; i++)	// Durchlauf der Koordinaten der letzten 3 Schüsse des Gegners 
		{
			j = 0;
			do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden 
			{
				if ( (Last3ShotsOfOpponent.at(i).x == (CriticalStartCoordinates.x + j)) & (Last3ShotsOfOpponent.at(i).y == CriticalStartCoordinates.y) )
				{
					Hit = 1;
				}
				j++;										// nächste Koordinate
			} while ((j < Ships[ShipNumber].Length) & (Hit != 1));
		}



		// Check, ob das ganze Schiff nach dem Bewegen noch im Spielfeld
		InsideBattlefield = true;
		j = 0;				// Zum Durchlaufen der Schifssfelder
		do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden
		{
			InsideBattlefield =  ((CriticalStartCoordinates.x + j) <= 9) && ((CriticalStartCoordinates.x + j) >= 0);// Beim Linksdrehen ist das Schiff in y-Richtung sicher immer innerhalb des Spielfeldes, weil
																					// Ausrichtung_aktuell = Down -> Ausrichtung_neu = Right. Nur die x-Koordinaten müssen gecheckt werden
			j++;																	// nächste Koordinate
		} while ((j < Ships[ShipNumber].Length) & (InsideBattlefield == true));




		// Wenn bei Prüfung, Collision, Hit, InsideBattlefield alles in Ordnung, dann kann das Schiff tatsächlich gedreht werden
		// keine Kollison(0), kein Schuss(0), im Spielfeld drin(1)
		if (!Collision & !Hit & InsideBattlefield)
		{
			Ships[ShipNumber].StartPos = CriticalStartCoordinates;		// Neue Startposition übernehmen
			Ships[ShipNumber].Orientation = NewOrientation;				// Neue Ausrichtung übernehmen 
			return 1;						// Bewegen erfolgreich
		}
		else
		{
			return 0;						// Bewegen nicht möglich
		}

	}

	cout << "Fehler in Funktion Move()";
	return 0;
}





Position Player::FindAttackShot(AttackResult LastAttackResult)
{
	// Gibt je nach gewählter Angriffsstrategie (AttackStrategy) eines Spielers Koordinaten zurück, auf die geschossen werden soll
	// Übergabe von Ergebnis dees letzten eigenen Schusses (Treffer, Versenkt)

	switch (AttackStrategy)
	{											// hier müssen noch korrekte Aufrufe der Strategiefunktionen eingefügt werden!
	case 1:
		return AttackStrategy1();

	case 2:
		return AttackStrategy2();

	case 3:
		return AttackStrategy3();

	case 4:
		return AttackStrategy4(&LastAttackResult.Hit, &LastAttackResult.Sunk);

	default:
		return { -1, -1 };
	}

}





void Player::DefensiveAction()
{	
	// Ermittelt entsprechend Verteidigungsstrategie einen Verteidigungsmove: 
	// Bewegen oder Drehen und welches Schiff, oder auch gar nichts
	// Ruft ggf. Funktion Turn oder Move auf 


	int ShipNumber;			// Nummer des Schiffes, das Bewegt/ Gedreht werden soll
	DefendAction Action;	// Angabe ob gedreht oder Bewegt werden soll
	MoveDirection MoveDir;	// Angabe in welche Richtung bewegt werden soll. Wenn bewegt werden soll, wird MoveDir ignoriert
	TurnDirection TurnDir;	// Angabe in welche Richtung gedreht werden soll. Wenn bewegt werden soll, wird MoveDir ignoriert

	bool ActionSuccessful = 1;	// Angabe ob Drehen/ Bewegen ausgeführt werden konnte

	do
	{
		/*	ShipNumber = 0;
			Action = DefendAction::Turn;
			MoveDir = MoveDirection::Forward;*/
			DefenseStrategy1(&ShipNumber, &Action, &MoveDir, &TurnDir );// Ermittelt Verteidigungsmove -> Schreibt entsprechende Werte in DefendAction, ShipNumber, MoveDir, TurnDir
		
		switch (Action)
		{
		case DefendAction::Nothing:
			ActionSuccessful = 1;
			break;
		case DefendAction::Move:
			ActionSuccessful = Move(ShipNumber, MoveDir);
			ActionSuccessful = 1;
			break;
		case DefendAction::Turn:
			ActionSuccessful = Turn(ShipNumber);
			break;
		default:
			cout << "Fehler bei ausgewählter Verteidigungs-Aktion";
		}
	
	}while (ActionSuccessful == 0);			// Wenn das Bewegen/Drehen so nicht möglich war wie von Strategie vorgegeben, muss Strategie neue Aktion wählen

}





Player::Player(int ModeSetShips) {
	 // Konstruktor 
	 // Stößt Konstruktor für jedes Schiff an
	 // legt Größe von Last3ShotsOfOpponent fest und initialisiert mit NULL
	 // Wählt zufällig AttackStrategy und DefenseStrategy aus

	// Einlesen der Initialisierungswerte der Schiffe aus Textdatei
	// Eigentlich mit Lexikalischer Analyse:
	// ...
	// Vorläufige Lösung: Direktes, festes Initialisieren; Korrekte Lösung kommt noch

	string NameDocSetShips;		// Name der Datei, die zum Setzen der Schiffe bei Spielbeginn genutzt werden soll
	int NumberTextDocShips;		// Nummer der Datei zum Schiffe Setzen 1...4
	// Datei zum Setzen der Schiffe je nach gewähltem Modus auswählen
	switch (ModeSetShips)
	{
		case 1: 
			NumberTextDocShips = (rand() % 4) + 1;		// Nummer der Textdatei, die zum Setzen der Schiffe bei Spielbeginn genutzt werden soll. Zahlen von 1...4
			switch (NumberTextDocShips)
			{
				case 1: 
					NameDocSetShips = "SetShips.txt"; 
					break;
				case 2: 
					NameDocSetShips = "SetShips.txt";	// hier müssen noch die Dateinamen angepasst werden
					break;
				case 3:
					NameDocSetShips = "SetShips.txt";
					break;
				case 4:
					NameDocSetShips = "SetShips.txt";
					break;
				default:
					cout << "Fehler bei NumberTextDocShips.txt";
					break;
			}
			break;
		case 2: 
			NameDocSetShips = "SetShips.txt";
			break;
		default:
			cout << "Fehler bei ModeSetShips";
			break;
	}

	lex(NameDocSetShips);		// Aufruf lexikalische Analyse

	//Ships[0].Length = 5;
	//Ships[0].StartPos = { 0,0 };
	//Ships[0].Orientation = Direction::Down;
	//Ships[0].Status.resize(Ships[0].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[0].Sunk = 0;							// Noch keine Treffer, noch nicht versenkt

	//Ships[1].Length = 4;
	//Ships[1].StartPos = { 4,2 };
	//Ships[1].Orientation = Direction::Right;
	//Ships[1].Status.resize(Ships[1].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[1].Sunk = 0;

	//Ships[2].Length = 4;
	//Ships[2].StartPos = { 8,6 };
	//Ships[2].Orientation = Direction::Down;
	//Ships[2].Status.resize(Ships[2].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[2].Sunk = 0;

	//Ships[3].Length = 3;
	//Ships[3].StartPos = { 0,7 };
	//Ships[3].Orientation = Direction::Right;
	//Ships[3].Status.resize(Ships[3].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[3].Sunk = 0;

	//Ships[4].Length = 3;
	//Ships[4].StartPos = { 2,3 };
	//Ships[4].Orientation = Direction::Down;
	//Ships[4].Status.resize(Ships[4].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[4].Sunk = 0;

	//Ships[5].Length = 3;
	//Ships[5].StartPos = { 5,4 };
	//Ships[5].Orientation = Direction::Down;
	//Ships[5].Status.resize(Ships[5].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[5].Sunk = 0;

	//Ships[6].Length = 2;
	//Ships[6].StartPos = { 3,0 };
	//Ships[6].Orientation = Direction::Right;
	//Ships[6].Status.resize(Ships[6].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[6].Sunk = 0;

	//Ships[7].Length = 2;
	//Ships[7].StartPos = { 9,0 };
	//Ships[7].Orientation = Direction::Down;
	//Ships[7].Status.resize(Ships[7].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[7].Sunk = 0;

	//Ships[8].Length = 2;
	//Ships[8].StartPos = { 9,3 };
	//Ships[8].Orientation = Direction::Down;
	//Ships[8].Status.resize(Ships[8].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[8].Sunk = 0;

	//Ships[9].Length = 2;
	//Ships[9].StartPos = { 3,9 };
	//Ships[9].Orientation = Direction::Right;
	//Ships[9].Status.resize(Ships[9].Length, 0);  // Alle Elemente von Status auf 0 setzen -> noch keine Treffer
	//Ships[9].Sunk = 0;


	for (int i = 0; i < 10; i++)
	{
		Ships[i].Status.resize(Ships[i].Length, 0);  // Größe des Vektors anpassen. Alle Elemente von Status auf 0 setzen -> noch keine Treffer
		Ships[i].Sunk = 0;							 // Noch keine Treffer, noch nicht versenkt
	}

	// Spieler 1 und Spieler 2 dürfen NICHT DIESELBE ANGRIFFSSTRAGTEGIE haben!!!
	static int Number_AttackStrategy_OtherPlayer = -1 ;			// Speichern der Strategiewahl (1...4) des anderen Spielers. Wenn noch keine Strategie für einen Spieler gewählt, dann = -1

	AttackStrategy = (rand() % 4) + 1;							// Zahlen von 1...4

	if (Number_AttackStrategy_OtherPlayer == -1)				// erster Spieler für ein Spiel wird erstellt, es wurde noch keine Strategie für einen Spieler in diesem Spiel gewählt
	{
		Number_AttackStrategy_OtherPlayer = AttackStrategy;		// Strategiewahl für ersten Speieler in diesem Spiel wird gespeichert
	}
	else if (Number_AttackStrategy_OtherPlayer != -1)			// zweiter Spieler für ein Spiel wird erstellt, es wird zum zweiten Mal eine Strategie für einen Spieler in diesem Spiel ermittelt
	{
		while (AttackStrategy == Number_AttackStrategy_OtherPlayer)	// es müssen unterscheidliche Strategien für beide Spieler in einem Spiel gewählt werden
		{
			AttackStrategy = (rand() % 4) + 1;					// Zahlen von 1...4 für die Wahl der Stratgie
		}
		Number_AttackStrategy_OtherPlayer = -1;					// Strategien für beide Spieler wurden gewählt, die zuletzte gespeicherte Strategienummer soll für das nächste Spiel irrelevant sein
	}
	
	
	DefenseStrategy = 1;							// Verteidigungsstrategie gibt es momentan nur eine -> immer diese wird gewählt

	Last3ShotsOfOpponent.resize(3, { -1, -1 });		// Noch keine Schüsse abgefeuert -> -1 für Abfragen

	Lost = 0;

	HitShotsOfOpponent = 0;
	MissedShotsOfOpponent = 0;
	SunkShipsByOpponent = 0;


}







void Player::lex(string FileName)
{
	FILE* inputFile;														// File-Ptr für die Schiffspositionsdateien
	char inputFileName[20];													// Name der Datei als char-Array (aus Parameter)
	strncpy_s(inputFileName, FileName.c_str(), sizeof(inputFileName));		// string in char-Array kopieren


	fopen_s(&inputFile, inputFileName, "r");

	if (inputFile == NULL) {
		cout << "Cannot open input file" << FileName << endl;
		return;
	}
	//cout << "Open: " << inputFileName << endl;

	CParser obj;
	obj.InitParse(inputFile, stderr, stdout);
	obj.yyparse(this);


	return;
}




