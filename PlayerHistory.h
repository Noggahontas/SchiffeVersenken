#pragma once
# include "Player.h"


class PlayerHistory
{
public:

	int AttackStrategy;
	int DefenseStrategy;
	int MissedShots;
	int HitShots;
	int SunkShips;
	int Lost;

	void Save(Player& PlayerHimself, Player& Opponent);		// Speichert Ergenisse eines Spieles von einem Spieler ab		
															// Übergabe des Speiers selbst, für den absgespeichert werden soll  
															// und Übergabe des Gegnsers, da bei ihm weitere Werte (MissedShotsOfOpponent, HitSchotsOfOpponent, SunkShipsByOpponent) 
};

