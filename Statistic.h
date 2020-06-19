#pragma once
#include"PlayerHistory.h"


class Statistic							// Statistik für eine Angriffsstrategie
{
	public:

		float MissedShots;
		float HitShots;
		float SunkShips;
		float Lost;
		float ProbabilityOfWinning;				// Wahrscheinlich keit zu gewinnen in Prozent
		int NumberOfGamesUsed;					// Wie oft die Strategie zum Einsatz kam 


		/*
			Funktion: Fügt der Statistik für eine Angriffsstrategie Werte von einem Spiel hinzu. Addieren der Ergebniswerte
			Input: GameHistory: Ergebnisse aus einem Spiel für einen Spieler
			Transienten: Alle Klassenvariablen
		*/
		void add(PlayerHistory& GameHistory);


		/*
			Funktion: Berechnet Statistik für diese Angriffsstrategie
			Transienten: Alle Klassenvariablen
		*/
		void Calculate();						


		/*
			Funktion: Standartkonstruktor, Initialsisireung
			Transienten: Alle Klassenvariablen
		*/
		Statistic();					
};


