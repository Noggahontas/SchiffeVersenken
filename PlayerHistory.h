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
															// �bergabe des Speiers selbst, f�r den absgespeichert werden soll  
															// und �bergabe des Gegnsers, da bei ihm weitere Werte (MissedShotsOfOpponent, HitSchotsOfOpponent, SunkShipsByOpponent) 
};

