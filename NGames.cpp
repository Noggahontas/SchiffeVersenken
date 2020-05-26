#include "stdafx.h"
#include "NGames.h"
#include "OneGame.h"
#include <iostream>
#include "DisplayOutput.h"

void NGames()
{
	int NumberOfGames;
	cout << "Wie viele Spiele sollen gespielt werden?\t";
	cin >> NumberOfGames;
	vector <PlayerHistory[2]> GameHistory(NumberOfGames);	// Speichern der Erbenisse f�r jedes Spiel von jeweils beiden Spielern

	// Kann man hier noch eine Startgrafik ausgeben?
	//F�r die graphische Ausgabe, dass man hier schon etwas zu sehen hat
	//DisplayOutput Graphics;
	//int Kaestchengroesse = 20;
	//int FarbeSchiffe = BLAU;
	//Graphics.Ausgabe(Kaestchengroesse, P[0], P[1], FarbeSchiffe, FarbeSchiffe);// Ausgabe Graphics

	for (int i = 0; i < NumberOfGames; i++)
	{
		OneGame(GameHistory.at(i));			// Ein Spiel wird ausgef�hrt
	}


	// So Funktioniert Zuweisung, zum Testen f�r Funtionsparameter
	//PlayerHistory(&GameResult)[2] = GameHistory.at(0);
}