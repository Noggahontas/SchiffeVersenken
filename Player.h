#pragma once
#include "Ship.h"
#include "Global_Definitions.h"
#include <vector>
using namespace std;


class Player
{
public:
	Ship Ships[10];							//Array vom Typ/Klasse Ships; alle 10 Schiffe, die ein Spieler besitzt
	vector<Position> Last3ShotsOfOpponent;	// Hier werden die letzten 3 Sch�sse des Gegners gespeichert. [0]=aktuellster Schuss, [2]= Schuss vor 2 Runden.  Am Anfang alle Elemente = NULL
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

	bool Move(int ShipNumber, MoveDirection Direction);	// �bergabe welches Schiff bewegt werden soll. Nummer Schiff = Index i aus Array Ships[i] 
														// �bergabe Richtung, in die bewegt werden soll. LeftMove, RightMove, UpMove, DownMove
														// Kollisionsabfrage ob Drehen m�glich, wenn ja:
														// �ndert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
														// R�ckgabe ob Bewegen m�glich/erfolgreich war. Geklappt=1, Nicht geklappt=0

	Player();		// Konstruktor 
					// St��t Kontruktor f�r jedes Schiff an
					//legt Gr��e von Last3ShotsOfOpponent fest und initialisiert mit NULL
					// W�hlt zuf�llig AttackStrategy und DefenseStrategy aus

	
														
};



/*
Zum Testen


	vector <int> test(3);
	test.at(0) = 1;
	test.at(1) = 2;
	test.at(2) = 3;
	//test.at(3) = 4;

	cout << test.at(0) << "\n" << test.at(1) << "\n" << test.at(2);

*/