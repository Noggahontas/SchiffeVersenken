#include "stdafx.h"
#include "OneGame.h"
#include "Global_Definitions.h"
#include "Alternate.h"
#include <Windows.h>		// benötogt für Funktion sleep()
#include <iostream>
#include "DisplayOutput.h"
#include "PlayerHistory.h"


bool OneGame(PlayerHistory (&GameResult)[2], int ModeSetShips, DisplayOutput &Graphics, bool FastPlayThrough, int WaitTime)
{

	Player P[2]{ (ModeSetShips), (ModeSetShips) };			// Spieler werden erstellt -> Parameterkonstruktor
	P[0].AttackStrategy = 3;
	P[1].AttackStrategy = 3;

	/*if (P[0].ReadInError == true || P[0].ReadInError == true)	//Falls beim Einlesen der Dateien zum Schiffe setzen ein Fehler passiert ist, Abbrechen der Funktion
	{
		return true;		// Es ist ein Fehler passiert, Datei hatte falsches Einleseformat
	}*/
	Position AttackShot;					// Koordinaten für Schuss beim Angreifen werden hier gespeichert
	AttackResult Result[2] = {false,false};	// Angabe ob vom Schuss AttackShot ein Schiff getroffen wurde:  Result.Hit: 1 = ein Schiff wurde getroffen,  0 = kein Schiff getroffen
											// Angabe ob vom Schuss AttackShot ein Schiff versenkt wurde:  Result.Sunk: 1 = ein Schiff wurde versenkt, 0 = kein Schiff versenkt
											// Für jeden Spieler eine Variable, notwendig für Strategien (benötogen die Infos)

	int i = 0;								// Zum Wechseln zwischen Spieler 0 und 1 

	int FarbeSchiffe = BLAU;				// Farbe der Schiffe

	
	if (!FastPlayThrough)											// Nur wenn Modus = langsam sollen Wartezeit und Ausgabe eingebaut werden
	{
		Sleep(WaitTime); 											// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus
		Graphics.Ausgabe(P[0], P[1], FarbeSchiffe, FarbeSchiffe);	// Graphische Ausgabe
	

	//Angriff von erstem Spieler
		cout << "\n\nSpieler " << i+1 << " an der Reihe: Angriff \n";
	}

	AttackShot = P[i].FindAttackShot(Result[i]);					// Durch ausgewählte Strategie des Spielers P[0] werden Koordinaten ausgewählt, auf die geschossen werden soll
	Result[i] = P[Alternate(i)].ShotOn(AttackShot);					// Auf ausgewählte Koordinaten wird geschossen: Schuss auf Spielfeld von zweitem Spieler P[1] 
	
	
	if ((!FastPlayThrough))											// Nur wenn Modus = langsam sollen Wartezeit und Ausgabe eingebaut werden
	{ 
		Sleep(WaitTime); 											
		Graphics.Ausgabe(P[0], P[1], FarbeSchiffe, FarbeSchiffe);	// Graphische Ausgabe 
	

		if (Result[i].Hit == 1)										// Ausgabe Resultat des Schusses von P[0]
		{
			cout << "Treffer \n";
			if (Result[i].Sunk == 1)
			{
				cout << "Schiff wurde versenkt \n";		
			}
		}
		else
		{
			cout << "Kein Treffer \n";
		}

		Sleep(WaitTime);
	}




	while (!P[0].Lost & !P[1].Lost)	// Solange noch kein Spieler verloren hat, wird weitergespielt
	{

		i = Alternate(i);			// ändert i: 1->0 , 0->1 ; Anderer Spieler an der Reihe


		// Prüfen ob Bwegen/Drehen noch erlaubt ist. Wenn bei jedem Spieler nur noch jewils 2 Schiffe übrig sind, darf nicht mehr bewegt weredn.
		if( (P[i].SunkShipsByOpponent < 8) || (P[Alternate(i)].SunkShipsByOpponent < 8) )
		{
			if (!FastPlayThrough)
			{ 
				// Bewegen noch erlaubt -> Verteidigung von Spieler i
				cout << "Spieler " << i + 1 << " an der Reihe: Drehen/Bewegen \n";
			}
			P[i].DefensiveAction();											// Durch gewählte Verteidigungsstrategie des jew. Spielers wird Aktion zum Verteidigen ausgweählt und ausgeführt
			
			if (!FastPlayThrough)											// Nur wenn Modus = langsam sollen Wartezeit und Ausgabe eingebaut werden
			{
				Sleep(WaitTime); 											
				Graphics.Ausgabe(P[0], P[1], FarbeSchiffe, FarbeSchiffe);	// Ausgabe Graphics
			}
		}
		else
		{
			if (!FastPlayThrough)
			{
				// Bewegen nich mehr erlaubt
				cout << "Es darf nicht mehr bewegt/gedreht werden, da jeweils nur noch zwei Schiffe uebrig sind \n";
			}
		}

		if (!FastPlayThrough)
		{ 
			Sleep(WaitTime);											
										
		// Angriff von Spieler i
			cout << "Spieler " << i + 1 << " an der Reihe: Angriff \n";
		}
		AttackShot = P[i].FindAttackShot(Result[i]);					// Durch ausgewählte Strategie des Spielers werden Koordinaten ausgewählt, auf die geschossen werden soll
																		// Übergabe von Ergebnissen (Treffer?, Versenkt?) des letzten eigenen Schusses
		Result[i] = P[Alternate(i)].ShotOn(AttackShot);					// Auf ausgewählte Koordinaten wird geschossen (auf Spielfeld von zweitem Spieler )

		if (!FastPlayThrough)											// Nur wenn Modus = langsam sollen Wartezeit und Ausgabe eingebaut werden
		{
			Sleep(WaitTime); 											
			Graphics.Ausgabe(P[0], P[1], FarbeSchiffe, FarbeSchiffe);	// Ausgabe Graphics
		

			if (Result[i].Hit == 1)
			{
				cout << "Treffer \n";
				if (Result[i].Sunk == 1)
				{
					cout << "Schiff wurde versenkt \n";
				}
			}
			else
			{
				cout << "Kein Treffer \n";
			}

			Sleep(WaitTime); 											
		}
	}

	if (!FastPlayThrough)													// Nur wenn Modus = langsam sollen Wartezeit und Ausgabe eingebaut werden
	{
		cout << "\n";
		//Beim Verlassen der Schleife hat ein Spieler verloren

		if (P[0].Lost == true)		// Wenn Spieler 0 verloren hat, hat Spieler 1 gewonnen
		{
			i = 1;
		}
		else 
		{
			i = 0;					// Wenn Spieler 1 verloren hat, hat Spieler 0 gewonnen
		}	
		cout << "Spieler " << i+1 << " hat gewonnen!";

		cout << "\nErgebnisse des Spiels:\n";
		cout << "Spieler 1: \n";
		// Beispiel: getroffene Schüsse von Spieler 0 sind in HitShotsOfOpponent bei Spieler 1 gespeichert
		cout << "Strategie Nr. " << P[0].AttackStrategy << "\n";
		// Beispiel: getroffene Schüsse von Spieler 0 sind in HitShotsOfOpponent bei Spieler 1 gespeichert
		cout << "Getroffene Schuesse: " << P[1].HitShotsOfOpponent << "\nVerfehlte Schuesse: " << P[1].MissedShotsOfOpponent << "\nVersenkte Schiffe: " << P[1].SunkShipsByOpponent << "\n";
		cout << "Spieler 2: \n";
		cout << "Strategie Nr. " << P[1].AttackStrategy << "\n";
		cout << "Getroffene Schuesse: " << P[0].HitShotsOfOpponent << "\nVerfehlte Schuesse: " << P[0].MissedShotsOfOpponent << "\nVersenkte Schiffe: " << P[0].SunkShipsByOpponent << "\n";
		cout << "___________________________________________________________\n";

		Sleep(WaitTime); 											
	}

	//Abspeichern der Spielergebnisse für jeden Spieler in übergebenes Array (Teil des Vektors GameHistory in Funktion NGames())
	GameResult[0].Save(P[0], P[1]);				
	GameResult[1].Save(P[1], P[0]);

	return false;
}

