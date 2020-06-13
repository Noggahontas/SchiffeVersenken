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
															// �bergabe des Speiers selbst, f�r den absgespeichert werden soll  
															// und �bergabe des Gegnsers, da bei ihm weitere Werte (MissedShotsOfOpponent, HitSchotsOfOpponent, SunkShipsByOpponent) 
};

