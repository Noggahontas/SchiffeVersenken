#pragma once
#include "Ship.h"
#include "Global_Definitions.h"
#include <vector>

class Player
{
public:
	Ship Ships[10];							//Array vom Typ/Klasse Ships; alle 10 Schiffe, die ein Spieler besitzt
	vector<Position> Last3ShotsOfOpponent;	// Hier werden die letzten 3 Schüsse des Gegners gespeichert. [0]=aktuellster Schuss, [2]= Schuss vor 2 Runden
	int AttackStrategy;						// Hier wird ein Schlüssel entsprechend der gewählten Angriffsstrategie gespeichert
	int DefenseStrategy;					// Hier wird ein Schlüssel entsprechend der gewählten Verteidigungsstrategie gespeichert

public:
	bool ShotOn(Position Shot);				// Schuss von Gegner auf Koordinaten Shot	
											// ändert Last3ShotsOfOpponent
											// Gibt zurück ob ein Schiff getroffen wurde: 1 = getroffen, 0= nicht getroffen
	bool Turn(int ShipNumber, TurnDirection Direction); // Übergabe welches Schiff gedreht werden soll. Nummer Schiff = Index i aus Array Ships[i] 
														// Übergabe Richtung, in die gedrecht werden soll. Left=1 oder Right=2
														// Kollisionsabfrage ob Drehen möglich, wenn ja:
														// Ändert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
														// Rückgabe ob Drehen möglich/erfolgreich war. Geklappt=1, Nicht geklappt=0
														
};

