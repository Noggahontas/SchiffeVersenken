#pragma once
#include"PlayerHistory.h"


class Statistic							// Statistik f�re ine Angriffsstrategie
{
	public:

		float MissedShots;
		float HitShots;
		float SunkShips;
		float Lost;
		float ProbabilityOfWinning;				// Wahrscheinlich keit zu gewinnen in Prozent
		int NumberOfGamesUsed;					// Wie oft die Strategie zum Einsatz kam 

		void add(PlayerHistory& GameHistory);	//F�gt der Statistik f�r eine Angriffsstrategie Werte von einem Spiel hinzu 

		void Calculate();						// Berechnet Statistik f�r diese Angriffsstrategie

		Statistic();							// Standartkonstruktor
};


