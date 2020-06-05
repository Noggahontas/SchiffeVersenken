#pragma once
#include "Player.h"
#include "PlayerHistory.h"

void OneGame(PlayerHistory(&GameResult)[2], int ModeSetShips);			// Spielablauf für 1 Spiel	
																		// Übergabe des 2-dimensionalen Vektors zum Abspeichern der Ergebnisse jedes Spiels für jeden Spieler