#pragma once
#include "Player.h"
#include "PlayerHistory.h"
#include "DisplayOutput.h"

void OneGame(PlayerHistory (&GameResult)[2], int ModeSetShips, DisplayOutput &Graphics);			// Spielablauf für 1 Spiel	
															// Übergabe des 2-dimensionalen Vektors zum Abspeichern der Ergebnisse jedes Spiels für jeden Spieler
															// Übergabe des Modus wie Schiffe am Anfang eines Spiels gesetzt werden sollen 
															// Übergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig für die Ausgabe