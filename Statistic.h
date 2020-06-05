#pragma once
#include"PlayerHistory.h"


class Statistic							// Statistik füre ine Angriffsstrategie
{
	public:

		float MissedShots;
		float HitShots;
		float SunkShips;
		float Lost;
		float ProbabilityOfWinning;				// Wahrscheinlich keit zu gewinnen in Prozent
		int NumberOfGamesUsed;					// Wie oft die Strategie zum Einsatz kam 

		void add(PlayerHistory& GameHistory);	//Fügt der Statistik für eine Angriffsstrategie Werte von einem Spiel hinzu 

		void Calculate();						// Berechnet Statistik für diese Angriffsstrategie

		Statistic();							// Standartkonstruktor
};


