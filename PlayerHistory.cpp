#include "stdafx.h"
#include "PlayerHistory.h"

void PlayerHistory:: Save(Player &PlayerHimself, Player& Opponent)
{
	// Speichert Ergenisse eines Spieles von einem Spieler ab		
	// �bergabe des Speiers selbst, f�r den absgespeichert werden soll  
	// und �bergabe des Gegnsers, da bei ihm weitere Werte f�r diesen Spieler gespeichert sind (MissedShotsOfOpponent, HitSchotsOfOpponent, SunkShipsByOpponent) 

	// Werte die beim Spieler selbst gespeichert sind, in die History abspeichern
	AttackStrategy = PlayerHimself.AttackStrategy;
	DefenseStrategy = PlayerHimself.DefenseStrategy;
	Lost = PlayerHimself.Lost;

	// Werte, die beim Gegner abgespeichert sind, in die History abspeichern
	MissedShots = Opponent.MissedShotsOfOpponent;
	HitShots = Opponent.HitShotsOfOpponent;
	SunkShips = Opponent.SunkShipsByOpponent;
}