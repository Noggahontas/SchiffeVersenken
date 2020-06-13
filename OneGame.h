#pragma once
#include "Player.h"
#include "PlayerHistory.h"
#include "DisplayOutput.h"

void OneGame(PlayerHistory (&GameResult)[2], int ModeSetShips, DisplayOutput &Graphics, bool FastPlayThrough);	
															// Spielablauf für 1 Spiel	
															// Übergabe eines Arrays mit 2 Elementen zum Abspeichern der Ergebnisse jedes Spiels für jeden Spieler (als Referenz)
															// Übergabe des Modus wie Schiffe am Anfang eines Spiels gesetzt werden sollen 
															// Übergabe der DisplayOutput Klassen-Variable Graphics als Referenz, notwendig für die Ausgabe
															// Übergabe ob alles im Schnelldurchlauf oder langsam erfolgen soll