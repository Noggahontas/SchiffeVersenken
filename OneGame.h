#pragma once
#include "Player.h"
#include "PlayerHistory.h"
#include "DisplayOutput.h"


/*
Funktion: Führt mehrere Spiele hintereinander aus und atellt Statistik für jede Strategie auf
Input:	- GameResult: Arrays mit 2 Elementen zum Abspeichern der Ergebnisse jedes Spiels für jeden Spieler (als Referenz)
		- ModeSetShips: Modus wie Schiffe am Anfang eines Spiels gesetzt werden sollen
		- Graphics: DisplayOutput Klassen-Objekt Graphics als Referenz, notwendig für die Ausgabe
		- FastPlayThrough: Modus ob alles im Schnelldurchlauf oder langsam erfolgen soll
		- WaitTime: Wartezeit zwischen Zügen in ms
Transienten: GameResult
*/

void OneGame(PlayerHistory (&GameResult)[2], int ModeSetShips, DisplayOutput &Graphics, bool FastPlayThrough, int WaitTime);	
															