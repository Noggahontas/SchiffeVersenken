#pragma once
#include "Player.h"
#include "PlayerHistory.h"

void OneGame(PlayerHistory(&GameResult)[2], int ModeSetShips);			// Spielablauf f�r 1 Spiel	
																		// �bergabe des 2-dimensionalen Vektors zum Abspeichern der Ergebnisse jedes Spiels f�r jeden Spieler