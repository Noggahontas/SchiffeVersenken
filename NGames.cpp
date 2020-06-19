#include "stdafx.h"
#include "NGames.h"
#include "OneGame.h"
#include <iostream>
#include "DisplayOutput.h"
#include "Statistic.h"
#include <iomanip>


void NGames(DisplayOutput &Graphics)
{
	// Führt mehere Spiele hintereinander aus
	// Anzahl der Spiele, die gespielt werden sollen werden vom Nutzer eingegeben
	// Übergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig für die graphische Ausgabe
	// Speichern der Ergebnisse von jedem Spiel für beide Spieler
	// Nachdem alle Spiele gespielt wurden, wird eine Statistik für jede Angriffsstrategie erstellt Übergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig für die Ausgabe


	int NumberOfGames;										// Nutzereingabe: Anzahl der Spiele, die gespielt werden sollen
	cout << "Wie viele Spiele sollen gespielt werden?\t";
	cin >> NumberOfGames;
	vector <PlayerHistory[2]> GameHistory(NumberOfGames);	// Speichern der Erbenisse für jedes Spiel von jeweils beiden Spielern -> Vektor, der als Elemente jeweils ein 2-Elemente-Array hat

	int ModeSetShips;										// Nutzereingabe: Wie sollen Schiffe bei Spielbeginn gesetzt werden

	int FastPlayThrough;									// Nutzereingabe: Schnelldurchlauf oder zum langsam Nachverfolgen

	int WaitTime = 0;										// Nutzereingabe: Bei Schnelldurchlauf Wartezeit zwischen Zügen in ms


	//Auswahl Nutzer zum Setzen der Schiffe bei Spielbeginn
	cout << "\nMoeglichkeit 1:\t Datei zum Setzen der Schiffe wird bei jedem Spielbeginn\n";
	cout << "\t\t und fuer jeden Spieler zufaellig gewaehlt -> Eingabe 1 \n";
	cout << "Moeglichkeit 2: Fuer jedes Spiel und beide Spieler immer eine bestimmte \n";
	cout << "\t\tDatei (\"SetShipsFix.txt\") fuer die Startpositionen der Schiffe nutzen -> Eingabe 2 \n";
	cout << "\nZur Auswahl Nummer der Moeglichkeit eingeben (1, 2):\t ";
	cin >> ModeSetShips;
	while ((ModeSetShips != 1) && (ModeSetShips != 2))				// Nur 1 oder 2 als Eingabe erlaubt, Möglichkeit zur Korrektur
	{
		cout << "\nEingabe ungueltig! Nur \"1\" oder \"2\" moeglich\n";
		cout << "\nZur Auswahl Nummer der Moeglichkeit eingeben (1, 2):\t";
		cin >> ModeSetShips;
	}
	
	// Angabe Nutzen ob alles im Schnelldurchlauf oder zum langsam Nachverfolgen ablaufen soll
	cout << "\n\nSoll das Spiel im Schnelldurchlauf erfolen? \nWenn ja, Eingabe 1 ansonsten Eingabe 0:\t";
	cin >> FastPlayThrough;
	while ((FastPlayThrough != 0) && (FastPlayThrough != 1))				// Nur 0 oder 1 als Eingabe erlaubt, Möglichkeit zur Korrektur
	{
		cout << "\nEingabe ungueltig! Nur \"0\" oder \"1\" moeglich\n";
		cout << "\nSchnelldurchlauf? (1 = ja, 0 = Nein):\t";
		cin >> FastPlayThrough;
	}

	// Angabe Nutzer wie lange die Wartezeit beim langsamen Durchlauf sein soll
	if (FastPlayThrough == 0)
	{
		cout << "\n\nGeben Sie die gewünschte Wartezeit zwischen Spielzuegen in ms an:\t";
		cin >> WaitTime;
	}


	// Gewünschte Anzahl an Spielen spielen lassen und Ergebnisse speichern
	for (int i = 0; i < NumberOfGames; i++)
	{
		OneGame(GameHistory.at(i), ModeSetShips, Graphics, FastPlayThrough, WaitTime);	// Ein Spiel wird ausgeführt 
																				// Übergabe von i-tem Element des Vektors zum Speichern der Ergebnisse am Ende eines Spiels 
	}



	//Erstellung der Statistiken für jede Angriffsstrategie
	Statistic AttackStrategy[4];							// Für jede Angriffstrategie wird eine Statistik erstellt
	int NumberAttStrat;
	int GameN;												// Nummer des Spiels 0...NumberOfGames
	int P ;													// Spieler 0 oder 1

	// Zuordnung der Ergebnisse zur den Angriffsstrategien
	for (GameN = 0;  GameN < NumberOfGames; GameN++)		// Durchlauf der Spiele
	{
		for (P = 0; P < 2; P++)								// Durchlauf der beiden Spieler
		{
			NumberAttStrat = GameHistory.at(GameN)[P].AttackStrategy;		// Nummer der Angriffsstrategie (1...4)
			AttackStrategy[NumberAttStrat-1].add(GameHistory.at(GameN)[P]);	// Die Ergebnisse des Spielers für dieses Spiel zur Statistik dieser Angriffsstrategie hinzufügen
			// Array für Strategiestatistik 0...3, Nummer der Angriffsstrategien in Player::AttackStrategy aber 1..4, darum -1
		}
	}

	// Ausgabe der Statistiken
	cout << "\n_____________________________________________________________\n";
	cout << "Ergebnis aus " << NumberOfGames << " Spielen. Statisken fuer jede Angriffsstrategie:\n\n";

	for (int i = 0; i < 4; i++)
	{
		AttackStrategy[i].Calculate();										// Werte für Statistik berechnen
		cout << "Angriffsstrategie " << i + 1 << ":\n";
		cout << "Gewinnwahrscheinlichkeit: " << setprecision(2) << fixed << AttackStrategy[i].ProbabilityOfWinning << " %\n";
		cout << "Durchnittliche versenkte Schiffe pro Spiel: " << fixed << AttackStrategy[i].SunkShips << "\n";
		cout << "Durchnittliche getroffene Schuesse pro Spiel: " << fixed << AttackStrategy[i].HitShots << "\n";
		cout << "Durchnittliche verfehlte Schuesse pro Spiel: " << fixed << AttackStrategy[i].MissedShots << "\n";
		cout << "Anzahl der Spiele, in der genutzt wurde: " << AttackStrategy[i].NumberOfGamesUsed << "\n\n";
	}


}

