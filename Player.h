#pragma once
#include "Ship.h"
#include "Global_Definitions.h"
#include <vector>

class Player
{
public:
	Ship Ships[10];							//Array vom Typ/Klasse Ships; alle 10 Schiffe, die ein Spieler besitzt
	vector<Position> Last3ShotsOfOpponent;	// Hier werden die letzten 3 Sch�sse des Gegners gespeichert. [0]=aktuellster Schuss, [2]= Schuss vor 2 Runden
	int AttackStrategy;						// Hier wird ein Schl�ssel entsprechend der gew�hlten Angriffsstrategie gespeichert
	int DefenseStrategy;					// Hier wird ein Schl�ssel entsprechend der gew�hlten Verteidigungsstrategie gespeichert

public:
	bool ShotOn(Position Shot);				// Schuss von Gegner auf Koordinaten Shot	
											// �ndert Last3ShotsOfOpponent
											// Gibt zur�ck ob ein Schiff getroffen wurde: 1 = getroffen, 0= nicht getroffen
	bool Turn(int ShipNumber, TurnDirection Direction); // �bergabe welches Schiff gedreht werden soll. Nummer Schiff = Index i aus Array Ships[i] 
														// �bergabe Richtung, in die gedrecht werden soll. Left=1 oder Right=2
														// Kollisionsabfrage ob Drehen m�glich, wenn ja:
														// �ndert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
														// R�ckgabe ob Drehen m�glich/erfolgreich war. Geklappt=1, Nicht geklappt=0
														
};

