#pragma once
#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <fstream>
//#include "AttackStrategy1.h"
//#include "AttackStrategy2.h"
//#include "AttackStrategy3.h"
//#include "AttackStrategy4.h"
#include "DefenseStrategy1.h"
#include <time.h>	// Für Generierung Zufallszahlen
using namespace std;
#include "PlayerLexan.h"
#include "Global_Definitions_Strategies.h"


AttackResult Player::ShotOn(Position Shot)
{
	// Schuss von Gegner auf Koordinaten Shot	
	// ändert Last3ShotsOfOpponent
	// Rückgabe als Strukt 
	// Gibt zurück ob ein Schiff getroffen wurde: Hit=1= getroffen, Hit=0=nicht getroffen
	// Gibt zurück ob ein Schiff versenkt wurde: Sunk=1=versenkt, Sunk=0=nicht versenkt

	Last3ShotsOfOpponent.insert(Last3ShotsOfOpponent.begin(), Shot);	//An Position 0 neuen Schuss des Gegners einfügen (Iterator auf Position 0 wird übergeben)
																		//Nun sind es 4 Elemente!
	Last3ShotsOfOpponent.pop_back();									//Letztes Element löschen -> Es sind wieder die letzten 3 Schüsse gespeichert

	AttackResult Result;					// Result.Hit: Angabe ob ein Schiff getroffen wurde
	Result.Sunk = false;					// Angabe ob ein Schiff versenkt wurde. Wenn kein Schiff getroffen wurde Sunk = 0
	
	int i = 0;
	do		// Ausführen bis ein getroffenes Schiff gefunden wurde, oder bis alle Schiffe durchgeschaut wurden
	{
		Result.Hit = Ships[i].IsHit(Shot);			// Funktion IsHit gibt zurück ob dieses Schiff getroffen wurde	// Speichern der Information ob ein Schiff durch disen Schuss getrofen wurde
		i++;
	} while ( (i < 10) & (Result.Hit != true) );	// in i steht jetzt (Nummer des Schiffes +1), das getroffen wurde

	if (Result.Hit == true)							
	{
		Result.Sunk = Ships[i-1].Sunk;				// Speichern ob ein Schiff durch diesen Schuss versenkt wurde um diese information zurück zu geben		
	}

	// Mitzählen für den Gegner, je nach dem ob ein Schiff getroffen und evtl. versenkt wurde
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
{	// Bewegt ein Schiff
	// Übergabe welches Schiff bewegt werden soll. Nummer Schiff = Index i aus Array Ships[i] 
	// Übergabe Richtung, in die bewegt werden soll: Forward oder Backward. ein Schiff kann nur in Längsrichtung bewegt werden
	// Kollisionsabfrage ob Bewegen möglich, wenn ja:
	// Ändert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
	// Rückgabe ob Bewegen möglich/erfolgreich war. Geklappt=1, Nicht geklappt=0

	

	Position CriticalCoordinates;	// Koordinaten, die Schiff nach dem Bewegen belegen würde
									// Für diese muss geprüft werden ob das möglich ist -> Kollision/ Außerhalb Spielfeld		

	bool Collision;					// Angabe ob es durch Bewegen eine Kollision mit einem Schiff gäbe

	bool Hit;						// Angabe ob es durch Bewegen eine Kollision mit einem Feld geben würde, das in den letzten 3 Runden abgeschossen wurde
		
	bool InsideBattlefield;			//Angabe ob nach Bewegen noch innerhalb von Schlachtfeld wäre

	// Abfrage ob das Schiff, das bewegt werden soll, schon einen Treffer kassiert hat -> getroffene Schiffe sind bewegungsunfähig
	for (int i = 0; i < Ships[ShipNumber].Length; i++)			// Durchlauf des gesamten Statusvektors
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
{	// Dreht ein Schiff
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

	bool InsideBattlefield;				// Angabe ob nach Bewegen noch innerhalb von Schlachtfeld wäre


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
		NewOrientation = Direction::Down;					// Ein Schiff, das nach rechts ausgerichtet ist, wird immer im Uhrzeigersinn gedreht -> neue Ausrichtung nach unten

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
		do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden bis eine Kollision entdeckt wurde oder bis alle Schiffe durchgeschaut
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
			do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden bis alle Koordinaten durch oder bis Übereinstimmung gefunden
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
		do					// Ausführen für alle Koordinaten (Anzahl = Länge Schiff), die durch Drehen belegt werden würden bis alle durchgeschaut oder bis Grenzüberschreitung gefunden
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
		NewOrientation = Direction::Right;						// Ein Schiff, das nach unten ausgerichtet ist, wird immer gegen den Uhrzeigersinn gedreht -> neue Ausrichtung nach rechts

		// Neue Startposition nach dem Drehen bestimmen. In Abhängigkeit der Länge des Schiffs
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
	{										
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


	int ShipNumber;			// Nummer des Schiffes, das bewegt/ gedreht werden soll
	DefendAction Action;	// Angabe ob gedreht oder bewegt werden soll oder gar nichts davon
	MoveDirection MoveDir;	// Angabe in welche Richtung bewegt werden soll. Wenn gedreht werden soll, wird MoveDir ignoriert

	bool ActionSuccessful = 1;	// Angabe ob Drehen/ Bewegen ausgeführt werden konnte

	do
	{
		DefenseStrategy1(&ShipNumber, &Action, &MoveDir );// Ermittelt Verteidigungsmove -> Schreibt entsprechende Werte in DefendAction, ShipNumber, MoveDir
		
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
	 // Parameterkonstruktor 
	 // Stößt Konstruktor für jedes Schiff an
	 // legt Größe von Last3ShotsOfOpponent fest und initialisiert mit -1
	 // Wählt zufällig AttackStrategy aus

	// Einlesen der Initialisierungswerte der Schiffe aus Textdatei

	string NameDocSetShips;		// Name der Datei, die zum Setzen der Schiffe bei Spielbeginn genutzt werden soll
	int NumberTextDocShips;		// Nummer der Datei zum Schiffe Setzen 1...4

	// Je nach gewähltem Modus Datei auswählen zum Setzen der Schiffe 
	switch (ModeSetShips)
	{
		case 1:		// Modus 1: Datei zum Schiffe setzen wird zufällig gewählt							
			NumberTextDocShips = (rand() % 4) + 1;		// Nummer der Textdatei, die zum Setzen der Schiffe bei Spielbeginn genutzt werden soll. Zahlen von 1...4
			switch (NumberTextDocShips)
			{
				case 1: 
					NameDocSetShips = "SetShips1.txt"; 
					break;
				case 2: 
					NameDocSetShips = "SetShips2.txt";	// hier müssen noch die Dateinamen angepasst werden
					break;
				case 3:
					NameDocSetShips = "SetShips3.txt";
					break;
				case 4:
					NameDocSetShips = "SetShips4.txt";
					break;
				default:
					cout << "Fehler bei NumberTextDocShips.txt";
					break;
			}
			break;
		case 2:		// Modus 2: Als Datei zum Schiffe setzen wird immer "SetShips.txt" genutzt
			NameDocSetShips = "SetShipsFix.txt";
			break;
		default:
			cout << "Fehler bei ModeSetShips";
			break;
	}

	lex(NameDocSetShips);		// Aufruf lexikalische Analyse



	for (int i = 0; i < 10; i++)
	{
		Ships[i].Status.resize(Ships[i].Length, 0);  // Größe des Vektors anpassen. Alle Elemente von Status auf 0 setzen -> noch keine Treffer
		Ships[i].Sunk = 0;							 // Noch keine Treffer, noch nicht versenkt
	}



	// Spieler 1 und Spieler 2 dürfen nicht dieselbe Angriffsstrategie haben!!! -> verhindern
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
		Number_AttackStrategy_OtherPlayer = -1;		// Strategien für beide Spieler in diesem Spiel wurden gewählt, die zuletzte gespeicherte Strategienummer soll für das nächste Spiel irrelevant sein
	}
	
	
	DefenseStrategy = 1;							// Verteidigungsstrategie gibt es momentan nur eine -> immer diese wird gewählt

	Last3ShotsOfOpponent.resize(3, { -1, -1 });		// Noch keine Schüsse abgefeuert -> -1 für Abfragen

	Lost = 0;

	HitShotsOfOpponent = 0;
	MissedShotsOfOpponent = 0;
	SunkShipsByOpponent = 0;

	SaveCoordinates = { };
	AttStrategy2Rounds = 0;
	AttStrategy3DirectionSet = false;
	AttStrategy3_4Direction = AttackDirection::N;
	AttStartegy4AlreadyShot = false;
	AttStrategy4DirectionChoice = false;
	AttStarategy4FieldBorder = false;
	AttStrategy4FirstHit = { };
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

	fclose(inputFile);

	return;
}






Position Player::AttackStrategy1()
{
	Position new_Position = { };

	new_Position.x = (rand() % 10);					// erzeugen einer Zufallszahl zwischen 0 und 9 für x und y
	new_Position.y = (rand() % 10);

	return new_Position;
}




Position Player::AttackStrategy2()
{
	int &Strategy_Rounds = AttStrategy2Rounds;		// Enthält die Nummer des aktuellen Durchlaufes

	Position &Pos = SaveCoordinates;				// beinhaltet die vorherigen Angriffskoordinaten 
													// und für die Rückgabe die neu bestimmen Koordinaten


	if ((Pos.x == NULL) && (Pos.y == NULL))			// Am Ende des letzten Durchlaufs muss von {0,0} zu {0,3} gewechselt werden
	{
		Pos.x = 0;
		Pos.y = 3;
		return Pos;
	}

	switch (Strategy_Rounds)						// Jeder Durchlauf hat unterschiedliche Start-/Endpunkte
	{
	case 0:											// Erster Durchlauf
		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
			if (Pos.x == 3)							// Endpunkt der ersten diagonalen Linie bei {3,0} -> return neuer Startpunkt 
			{
				Pos = { 0,7 };						// Startpunkt der neuen diagonalen Linie
				return Pos;
			}
			else if (Pos.x == 7)					// Endpunkt der zweiten diagonalen Linie bei {0,7} -> return neuer Startpunkt
			{
				Pos = { 2,9 };						// Startpunkt der neuen diagonalen Linie
				return Pos;
			}
			else if (Pos.y == 2)					// Endpunkt der dritten diagonalen Linie bei {9,2} -> return neuer Startpunkt
			{
				Pos = { 6,9 };						// Startpunkt der neuen diagonalen Linie
				return Pos;
			}
			else if (Pos.y == 6)					// Endpunkt der vierten diagonalen Linie bei {9,6} -> return neuer Startpunkt
			{
				Pos = { 0,2 };						// Startpunkt der neuen diagonalen Linie
				Strategy_Rounds = 1;				// Zweiter Durchlauf beim nächsten Aufruf
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;						// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
			Pos.y = Pos.y - 1;
			return Pos;
		}
	case 1:
		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
			if (Pos.x == 2)							// Endpunkt der ersten diagonalen Linie {0,9} -> return neuer Startpunkt
			{
				Pos = { 0,6 };						// Startpunkt der neuen diagonalen Linie
				return Pos;
			}
			else if (Pos.x == 6)
			{
				Pos = { 1,9 };
				return Pos;
			}
			else if (Pos.y == 1)
			{
				Pos = { 5,9 };
				return Pos;
			}
			else if (Pos.y == 5)
			{
				Pos = { 9,9 };
				return Pos;
			}
			else if (Pos.y == 9)
			{
				Pos = { 0,1 };
				Strategy_Rounds = 2;				// Dritter Durchlauf beim nächsten Aufruf
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;						// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
			Pos.y = Pos.y - 1;
			return Pos;
		}
	case 2:
		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
			if (Pos.x == 1)
			{
				Pos = { 0,5 };
				return Pos;
			}
			else if (Pos.x == 5)
			{
				Pos = { 0,9 };
				return Pos;
			}
			else if (Pos.y == 0)
			{
				Pos = { 4,9 };
				return Pos;
			}
			else if (Pos.y == 4)
			{
				Pos = { 8,9 };
				return Pos;
			}
			else if (Pos.y == 8)
			{
				Pos.x = 0;
				Pos.y = 4;
				Strategy_Rounds = 3;				// vierter Durchlauf beim nächsten Aufruf
				return Pos;
			}
		}
		else
		{
			Pos.x = Pos.x + 1;						// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
			Pos.y = Pos.y - 1;
			return Pos;
		}
	case 3:
		if ((Pos.x == 9) || (Pos.y == 0))			// Prüfen der ersten Reihe (y=0) oder der letzten Spalte (x=9), 
		{											// da dort das Spielfeld endet und von neuem Punkt aus gestartet werden soll.
			if (Pos.x == 4)
			{
				Pos = { 0,8 };
				return Pos;
			}
			else if (Pos.x == 5)
			{
				Pos = { 0,9 };
				return Pos;
			}
			else if (Pos.x == 8)
			{
				Pos = { 3,9 };
				return Pos;
			}
			else if (Pos.y == 3)
			{
				Pos = { 7,9 };
				return Pos;
			}
			else if (Pos.y == 7)
			{
				Pos.x = 0;
				Pos.y = 0;
				Strategy_Rounds = 0;			// Am Ende des vierten Durchlaufs wird wieder mit dem ersten Durchlauf
				return Pos;						// im nächsten Aufruf gestartet
			}
		}
		else
		{
			Pos.x = Pos.x + 1;					// Angriffsrichtung läuft diagonal rechts (x+1) hoch (y-1)
			Pos.y = Pos.y - 1;
			return Pos;
		}
	}

	return Pos;
}





Position Player::AttackStrategy3()
{
	AttackDirection &Richtung = AttStrategy3_4Direction;				// Für die Richtung, in die geschossen werden soll
	bool &Direction = AttStrategy3DirectionSet;						// notwendig zum unterscheiden zwischen Situation {NULL,NULL} und {0,0}

	Position& Pos = SaveCoordinates;	// beinhaltet die vorherige und dann die neu berechneten Koordinaten

	// Der erste Schuss von jedem Durchlauf startet bei {0,0} und hat als Richtung "Süden" ausgewählt
	if (((Pos.x == NULL) && (Pos.y == NULL) && (Direction == false)) || ((Pos.x == 5) && (Pos.y == 4)))
	{
		Pos.x = 0;
		Pos.y = 0;
		Richtung = AttackDirection::S;
		Direction = true;
		return Pos;
	}


	// Alle Koordinaten, die mit einem Richtungswechsel zusammenhängen (jeweils die Eckpunkte)
	Position S_to_E[5] = { {0,9} , {1,8} , {2,7} , {3,6} , {4,5} };		// Süd-Ost Richtungswechsel
	Position E_to_N[5] = { {5,5} , {6,6} , {7,7} , {8,8} , {9,9} };		// Ost-Nord Richtungswechsel
	Position N_to_W[5] = { {6,3} , {7,2} , {8,1} , {9,0} };				// Nord-West Richtungswechsel
	Position W_to_S[5] = { {1,0} , {2,1} , {3,2} , {4,3} };				// West-Süd Richtungswechsel

	// letzter Schuss mit den Eckpunkt-Koordinaten vergleichen, falls erreicht -> Richtungswechsel
	// Richtungswechsel von Süden nach Osten oder von Osten zu Norden prüfen
	for (int ii = 0; ii < 5; ii++)
	{
		if ((Pos.x == S_to_E[ii].x) && (Pos.y == S_to_E[ii].y)) { Richtung = AttackDirection::E; break; }
		else if ((Pos.x == E_to_N[ii].x) && (Pos.y == E_to_N[ii].y)) { Richtung = AttackDirection::N; break; }
	}
	// Richtungswechsel von Norden nach Westen oder von Westen nach Süden prüfen
	for (int ii = 0; ii < 4; ii++)
	{
		if ((Pos.x == N_to_W[ii].x) && (Pos.y == N_to_W[ii].y)) { Richtung = AttackDirection::W; break; }
		else if ((Pos.x == W_to_S[ii].x) && (Pos.y == W_to_S[ii].y)) { Richtung = AttackDirection::S; break; }
	}


	// Abhängig von der Angriffsrichtung werden neue Koordinaten berechnet
	switch (Richtung)
	{
	case AttackDirection::S:					// Angriffsrichtung ist Süden (z.B. die erste Spalte bei x=0)
	{
		Pos.x = Pos.x;							// x-Wert bleibt gleich
		Pos.y = Pos.y + 1;						// y-Wert wird inkrementiert
		return Pos;
		break;
	}
	case AttackDirection::E:					// Angriffsrichtung ist Osten (z.B. die letzte Zeile bei y=9)
	{
		Pos.x = Pos.x + 1;
		Pos.y = Pos.y;
		return Pos;
		break;
	}
	case AttackDirection::N:					// Angriffsrichtung ist Norden (z.B. die letzte Spalte bei x=9)
	{
		Pos.x = Pos.x;
		Pos.y = Pos.y - 1;
		return Pos;
		break;
	}
	case AttackDirection::W:					// Angriffsrichtung ist Westen (z.B. die erste Zeile bei y=0)
	{
		Pos.x = Pos.x - 1;
		Pos.y = Pos.y;
		return Pos;
		break;
	}
	default:
	{
		cout << "AttackStrategy2: Da stimmt was nicht!" << endl;
	}
	}
	return Pos;
}




// Teil von AttackStrategy 4

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


Position Player::AttackStrategy4(bool* LastShotHit, bool* sunk)
{
	Position& Pos = SaveCoordinates;				// Beinhaltet die Koordinaten des vorherigen Schusses bzw nach der Berechnung die neuen Angriffskoordinaten
	bool &alreadyShot = AttStartegy4AlreadyShot;	// Wenn schonmal geschossen wurde (true) -> für bestimmte Abfragen

	AttackDirection &Direction = AttStrategy3_4Direction;							// zeigt die Angriffsrichtung an für den nächsten
	bool &DirectionChoice = AttStrategy4DirectionChoice;		// zur Unterscheidung zwischen neuen rnd-Koordinaten und Richtungswechselabfrage

	bool &FieldBorder = AttStarategy4FieldBorder;			// Kollision mit dem Spielfeldrand muss gesondert behandelt werden

	Position &first_hit = AttStrategy4FirstHit;				// merken des ersten Schusses (die ersten rnd-Koordinaten bei jeder Suchfolge)


	// Erster Schuss (Bedingungen: x und y = NULL) -> rnd-Koordinaten zurückgeben
	// ODER
	// Ging vorherige Schuss daneben UND es wurde schon geschossen UND Richtung noch nicht gewählt -> neue rnd-Koordinaten zurückgeben
	// ODER
	// Der vorherhige Schuss hat ein Schiff versenkt -> neue rnd-Koordinaten zurückgeben
	if (((Pos.x == NULL) && (Pos.y == NULL) && (alreadyShot == false)) || ((*LastShotHit == false) && (alreadyShot == true) && (!DirectionChoice)) || (*sunk == true))
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
		else if ((Direction == AttackDirection::E) || ((Direction == AttackDirection::E) && ((Pos.x + 1) > 9)))
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






void Player::DefenseStrategy1(int* ShipNumber, DefendAction* Action, MoveDirection* MoveDir)
{
	int rndAction = (rand() % 3);							// DefendAction (Nothing, Move, Turn) soll zufällig gewählt werden
	int rndMoveDir = 0;										// Zufällige Bewegungsrichtung wählen

	switch (rndAction)
	{
	case 0:													// Erster Fall: nichts tun
		*Action = DefendAction::Nothing;					// DefendAction auf Nothing setzen
		break;

	case 1:													// Zweiter Fall: ein Schiff soll sich bewegen
		*Action = DefendAction::Move;						// DefendAction auf Move setzen
		*ShipNumber = (rand() % 10);						// zufälliges Schiff auswählen
		rndMoveDir = (rand() % 2);							// zufällige Richtungswahl
		switch (rndMoveDir)
		{
		case 0:											// Erster Fall: Vorwärts bewegen
			*MoveDir = MoveDirection::Forward;
			break;
		case 1:											// Zweiter Fall: Rückwärts bewegen
			*MoveDir = MoveDirection::Backward;
			break;
		}
		break;

	case 2:													// Dritter Fall: ein Schiff soll sich drehen
		*Action = DefendAction::Turn;						// DefendAction auf Turn setzen
		*ShipNumber = (rand() % 10);						// zufälliges Schiff auswählen
		break;
	}
	return;
}