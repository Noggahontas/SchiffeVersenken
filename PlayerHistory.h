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



	/*
		Funktion: Speichert Ergenisse eines Spieles von einem Spieler ab
		Input:	- PlayerHimself: Spieler selbst, für den absgespeichert werden soll
				- Opponent: Gegnsers, da bei ihm weitere Werte (MissedShotsOfOpponent, HitSchotsOfOpponent, SunkShipsByOpponent) gespeichert sind
		Transienten: alle Klassenvariablen
	*/
	void Save(Player& PlayerHimself, Player& Opponent);		
};

