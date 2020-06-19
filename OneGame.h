#pragma once
#include "Player.h"
#include "PlayerHistory.h"
#include "DisplayOutput.h"


/*
Funktion: F�hrt mehrere Spiele hintereinander aus und atellt Statistik f�r jede Strategie auf
Input:	- GameResult: Arrays mit 2 Elementen zum Abspeichern der Ergebnisse jedes Spiels f�r jeden Spieler (als Referenz)
		- ModeSetShips: Modus wie Schiffe am Anfang eines Spiels gesetzt werden sollen
		- Graphics: DisplayOutput Klassen-Objekt Graphics als Referenz, notwendig f�r die Ausgabe
		- FastPlayThrough: Modus ob alles im Schnelldurchlauf oder langsam erfolgen soll
		- WaitTime: Wartezeit zwischen Z�gen in ms
Transienten: GameResult
*/

void OneGame(PlayerHistory (&GameResult)[2], int ModeSetShips, DisplayOutput &Graphics, bool FastPlayThrough, int WaitTime);	
															