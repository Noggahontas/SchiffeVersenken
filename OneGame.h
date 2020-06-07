#pragma once
#include "Player.h"
#include "PlayerHistory.h"
#include "DisplayOutput.h"

void OneGame(PlayerHistory (&GameResult)[2], int ModeSetShips, DisplayOutput &Graphics);			// Spielablauf f�r 1 Spiel	
															// �bergabe des 2-dimensionalen Vektors zum Abspeichern der Ergebnisse jedes Spiels f�r jeden Spieler
															// �bergabe des Modus wie Schiffe am Anfang eines Spiels gesetzt werden sollen 
															// �bergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig f�r die Ausgabe