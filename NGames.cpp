#include "stdafx.h"
#include "NGames.h"
#include "OneGame.h"
#include <iostream>
#include "DisplayOutput.h"
#include "Statistic.h"
#include <iomanip>


void NGames(DisplayOutput &Graphics)
{
	// F�hrt meherere Speiler hintereinander aus, Anzahl der Spiele, die gespielt werden sollen werden vom Nutzer eingegeben
	// �bergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig f�r die Ausgabe


	int NumberOfGames;
	cout << "Wie viele Spiele sollen gespielt werden?\t";
	cin >> NumberOfGames;
	vector <PlayerHistory[2]> GameHistory(NumberOfGames);	// Speichern der Erbenisse f�r jedes Spiel von jeweils beiden Spielern

	int ModeSetShips;										// Nutzereingabe: Wie sollen Schiffe bei Spielbeginn gesetzt werden

	//Auswahl Nutzer zum Setzen der Schiffe bei Spielbeginn
	cout << "M�glichkeit 1:\t Datei zum Setzen der Schiffe wird bei jedem Spielbeginn\n";
	cout << "\t\t und f�r jeden Spieler zuf�llig gew�hlt -> Eingabe 1 \n";
	cout << "M�glichkeit 2: \tF�r jedes Spiel und beide Spieler immer eine bestimmte \n";
	cout << "\t\tDatei (\"SetShipsFix.txt\") f�r die Startpositionen der Schiffe nutzen -> Eingabe 2 \n";
	cout << "Zur Auswahl Nummer der M�glichkeit eingeben (1, 2):\t \n";
	cin >> ModeSetShips;
	while ((ModeSetShips != 1) && (ModeSetShips != 2))				// Nur 1 oder 2 als Eingabe erlaubt, M�glichkeit zur Korrektur
	{
		cout << "\nEingabe ung�ltig! Nur \"1\" oder \"2\" m�glich\n";
		cout << "Zur Auswahl Nummer der M�glichkeit eingeben (1, 2):\t \n";
		cin >> ModeSetShips;
	}
	

	// Kann man hier noch eine Startgrafik ausgeben?
	//F�r die graphische Ausgabe, dass man hier schon etwas zu sehen hat
	//DisplayOutput Graphics;
	//int Kaestchengroesse = 20;
	//int FarbeSchiffe = BLAU;
	//Graphics.Ausgabe(P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

	for (int i = 0; i < NumberOfGames; i++)
	{
		OneGame(GameHistory.at(i), ModeSetShips, Graphics);			// Ein Spiel wird ausgef�hrt
	}

	// So Funktioniert Zuweisung, zum Testen f�r Funtionsparameter
	//PlayerHistory(&GameResult)[2] = GameHistory.at(0);


	//Erstellung der Statistiken f�r jede Angriffsstrategie
	Statistic AttackStrategy[4];							// F�r jede Angriffstrategie wird eine Statistik erstellt
	int NumberAttStrat;
	int GameN;												//Nummer des Spiels 0...XX
	int P ;													// Spieler 0 oder 1
	// Zuordnung der Ergebnisse zur der Angriffsstrategien
	for (GameN = 0;  GameN < NumberOfGames; GameN++)		// Durchlauf der Spiele
	{
		for (P = 0; P < 2; P++)								// Durchlauf der beiden Spieler
		{
			NumberAttStrat = GameHistory.at(GameN)[P].AttackStrategy;		// Nummer der Angriffsstrategie (1...4)
			AttackStrategy[NumberAttStrat-1].add(GameHistory.at(GameN)[P]);	// Die Ergebnisse des Spielers f�r dieses Spiel zur Statistik dieser Angriffsstrategie hinzuf�gen
			// Array f�r Strategiestatistik 0...3, Nummer der Angriffsstrategien in Player::AttackStrategy aber 1..4, darum -1
		}
	}

	// Ausgabe der Statistiken
	cout << "\n_____________________________________________________________\n";
	cout << "Ergebnis aus " << NumberOfGames << " Spielen. Statisken f�r jede Angriffsstrategie:\n\n";

	for (int i = 0; i < 4; i++)
	{
		AttackStrategy[i].Calculate();										// Werte f�r Statistik berechnen
		cout << "Angriffsstrategie " << i + 1 << ":\n";
		cout << "Gewinnwahrscheinlichkeit: " << setprecision(2) << fixed << AttackStrategy[i].ProbabilityOfWinning << " %\n";
		cout << "Durchnittliche versenkte Schiffe pro Spiel: " << fixed << AttackStrategy[i].SunkShips << "\n";
		cout << "Durchnittliche getroffene Sch�sse pro Spiel: " << fixed << AttackStrategy[i].HitShots << "\n";
		cout << "Durchnittliche verfehlte Sch�sse pro Spiel: " << fixed << AttackStrategy[i].MissedShots << "\n";
		cout << "Anzahl der Spiele, in der genutzt wurde: " << AttackStrategy[i].NumberOfGamesUsed << "\n\n";
	}


}

