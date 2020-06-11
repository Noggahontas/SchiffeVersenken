#include "stdafx.h"
#include "Statistic.h"

void Statistic::add(PlayerHistory& GameHistory)
{
	//Fügt der Statistik für eine Angriffsstrategie Werte von einem Spiel hinzu 

	MissedShots = MissedShots + GameHistory.MissedShots;
	HitShots = HitShots + GameHistory.HitShots;
	SunkShips = SunkShips + GameHistory.SunkShips;
	Lost = Lost + GameHistory.Lost;
	NumberOfGamesUsed++;				// Wie oft die Strategie zum Einsatz kam -> 1 mal mehr
}

void Statistic::Calculate()
{
	if(NumberOfGamesUsed != 0)
	{ 
		MissedShots = MissedShots / (float)NumberOfGamesUsed;	// Durchsnittliche verfehlte Schüsse pro Spiel
		HitShots = HitShots / (float)NumberOfGamesUsed;			// Durchsnittliche getroffene Schüsse pro Spiel
		SunkShips = SunkShips / (float)NumberOfGamesUsed;		// Durchsnittliche versenkte Schiffe pro Spiel
		Lost = Lost / (float)NumberOfGamesUsed * 100;			// Wahrscheinlichkeit zu Verlieren in Prozent
		ProbabilityOfWinning = 100 - Lost;
	}
}

Statistic::Statistic()
{
	// Standartkonstruktor

	MissedShots = 0;
	HitShots = 0;
	SunkShips = 0;
	Lost = 0;
	ProbabilityOfWinning = 0;			// Wahrscheinlichkeit zu gewinnen in Prozent
	NumberOfGamesUsed = 0;				// Wie oft die Strategie zum Einsatz kam 

}
