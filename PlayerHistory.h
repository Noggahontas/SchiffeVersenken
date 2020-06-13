#pragma once
# include "Player.h"


class PlayerHistory			// Zum Abspeichern der Ergebnisse eines Spielers von einem Spiel
{
public:

	int AttackStrategy;
	int DefenseStrategy;
	int MissedShots;
	int HitShots;
	int SunkShips;			// Anzahl der Schiffe, die der Spieler in diesem Spiel versenkt hat
	bool Lost;				// Angabe ob der Spieler dieses Spiel verloren hat: true = verloren

	void Save(Player& PlayerHimself, Player& Opponent);		// Speichert Ergenisse eines Spieles von einem Spieler ab		
															// Übergabe des Speiers selbst, für den absgespeichert werden soll  
															// und Übergabe des Gegnsers, da bei ihm weitere Werte (MissedShotsOfOpponent, HitSchotsOfOpponent, SunkShipsByOpponent) 
};

