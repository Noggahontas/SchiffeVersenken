#include "stdafx.h"
#include "OneGame.h"
#include "Global_Definitions.h"
#include "Alternate.h"
#include <Windows.h>		// benötogt für Funktion sleep()
#include <iostream>
#include "DisplayOutput.h"
#include "PlayerHistory.h"


void OneGame(PlayerHistory (&GameResult)[2])		
{
	Player P[2];			// Spieler werden erstellt -> Standartkonstruktor

	P[0].AttackStrategy = 1;	// Zum Testen: Spieler 0 hat Spiralschießen
	P[1].AttackStrategy = 4;	// Spieler 1 hat Diagonalschießen

	//Für die graphische Ausgabe
	DisplayOutput Graphics;	
	int Kaestchengroesse = 20;
	int FarbeSchiffe = BLAU;


	// Für die zeitliche Verzögerung
	int WaitTime;
	cout << "Wie schnell soll das Spiel ablaufen? Angabe in ms:\t";
	cin >> WaitTime;

	Position AttackShot ;					// Koordinaten für Schuss beim Angreifen werden hier gespeichert
	AttackResult Result[2] = {0,0};			// Angabe ob vom Schuss AttackShot ein Schiff getroffen wurde:  Result.Hit: 1 = ein Schiff wurde getroffen,  0 = kein Schiff getroffen
											// Angabe ob vom Schuss AttackShot ein Schiff versenkt wurde:  Result.Sunk: 1 = ein Schiff wurde versenkt, 0 = kein Schiff versenkt
											// Für jeden Spieler eine Variable, notwendig für Strategien (benötogen die Infos)
	int i = 0;								// Zum Wechseln zwischen Spieler 0 und 1 

	Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics
	Sleep(WaitTime);										// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus


	//Angriff von erstem Spieler
	cout << "Spieler " << i+1 << " an der Reihe: Angriff \n";
	AttackShot = P[i].FindAttackShot(Result[i]);	// Durch ausgewählte Strategie des Spielers P[0] werden Koordinaten ausgewählt, auf die geschossen werden soll
	Result[i] = P[Alternate(i)].ShotOn(AttackShot);			// Auf ausgewählte Koordinaten wird geschossen: Schuss auf Spielfeld von zweitem Spieler P[1] 
	

	Sleep(WaitTime);										// Versetzt Programm für 2 Sekunden in einen inaktiven Modus
	Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

	if (Result[i].Hit == 1)								// Ausgabe Resultat des Schusses von P[0]
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

	Sleep(WaitTime);						// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus


	while (!P[0].Lost & !P[1].Lost)	// Solange noch kein Spieler verloren hat, wird weitergespielt
	{

		i = Alternate(i);			// ändert i: 1->0 , 0->1

		// Prüfen ob Bwegen/Drehen noch erlaubt ist. Wenn bei jedem Spieler nur noch jewils 2 Schiffe übrog sind, darf nicht mehr bewegt weredn.
		if( (P[i].SunkShipsByOpponent < 8) && (P[Alternate(i)].SunkShipsByOpponent < 8) )
		{
			// Verteidigung von Spieler i
			cout << "Spieler " << i + 1 << " an der Reihe: Drehen/Bewegen \n";
			//P[i].DefensiveAction(Result[Alternate(i)].Hit);					// Durch gewählte Verteidigungsstrategie des jew. Spielers wird Aktion zum Verteidigen ausgweählt und ausgeführt
																			// Übergabe, ob letzter Schuss des Gegners Treffer war
			Sleep(WaitTime);												// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus
			Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics
		}
		else
		{
			cout << "Es darf nicht mehr bewegt/gedreht werden, da jewils nur noch zwei Schiffe übrig sind \n";
		}

		Sleep(WaitTime);												// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus


		// Angriff von Spieler i
		cout << "Spieler " << i + 1 << " an der Reihe: Angriff \n";
		AttackShot = P[i].FindAttackShot(Result[i]);			// Durch ausgewählte Strategie des Spielers werden Koordinaten ausgewählt, auf die geschossen werden soll
		Result[i] = P[Alternate(i)].ShotOn(AttackShot);					// Auf ausgewählte Koordinaten wird geschossen (auf Spielfeld von zweitem Spieler )

		Sleep(WaitTime);												// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus
		Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

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

		Sleep(WaitTime);									// Versetzt Programm für bestimmte Zeit (WaitTime) in einen inaktiven Modus

	}

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
	cout << "Getroffene Schüsse: " << P[1].HitShotsOfOpponent << "\n Verfehlte Schüsse: " << P[1].MissedShotsOfOpponent << "\n Versenkte Schiffe: " << P[1].SunkShipsByOpponent << "\n";
	cout << "Spieler 2: \n";
	cout << "Strategie Nr. " << P[1].AttackStrategy << "\n";
	cout << "Getroffene Schüsse: " << P[0].HitShotsOfOpponent << "\n Verfehlte Schüsse: " << P[0].MissedShotsOfOpponent << "\n Versenkte Schiffe: " << P[0].SunkShipsByOpponent << "\n";
	cout << "___________________________________________________________\n";

	Sleep(3000);

	//Abspeichern der Spielergebnisse für jeden Spieler in übergebenes Array (Teil des Vektors GameHistory in Funktion NGames())
	GameResult[0].Save(P[0], P[1]);				
	GameResult[1].Save(P[1], P[0]);


}

