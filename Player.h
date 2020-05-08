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





//_________________________________________________________________________

// Testen Funktion Move

//Player P1;
//
//int i = 6; // Number of Ship to be moved
//
//MoveDirection Dir = MoveDirection::Forward;
//
//cout << "Orientation: " << static_cast <int> (P1.Ships[i].Orientation) << "\n";
//cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";
//
//cout << " Bewegen-Ergebnis: " << P1.Move(i, Dir) << "\n";
//cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";
//cout << "-----------------------------\n";
//cout << " Bewegen-Ergebnis: " << P1.Move(i, Dir) << "\n";
//cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";
//cout << "-----------------------------\n";
//cout << " Bewegen-Ergebnis: " << P1.Move(i, Dir) << "\n";
//cout << "StartPos: {" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "} \n";




//______________________________________________________________________________





// L�sung Problem enum -> Typumwandlung
//
//enum class Test { a, b, c };
//
//Test T;
//
//T = (Test)1;
//
//T = static_cast <Test> (2);





//_______________________________________________________________________________________
// Zum test ShotOn
//Player P1;
//
//cout << P1.ShotOn({ 5,2 });
//
//cout << "Status getr. Schiff: " << P1.Ships[1].Status.at(0) << P1.Ships[1].Status.at(1) << P1.Ships[1].Status.at(2) << P1.Ships[1].Status.at(3);
//
//cout << "\n letzte 3 Sch�sse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//cout << "\n" << P1.ShotOn({ 1,0 });
//cout << "\n letzte 3 Sch�sse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//cout << "\n" << P1.ShotOn({ 2,3 });
//cout << "\n letzte 3 Sch�sse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}


//______________________________________________________________________________________________________________

// Zum Testen Konstruktor
//
//Player P1;
//for (int i = 0; i < 10; i++)
//{
//	cout << "Ships[" << i << "]: " << P1.Ships[i].Length << "{" << P1.Ships[i].StartPos.x << P1.Ships[i].StartPos.y << "}" << P1.Ships[i].Sunk << "\n";
//}
//if (P1.Ships[0].Orientation == Direction::Down)
//{
//	cout << 1 << "\n";
//}
//else if (P1.Ships[0].Orientation == Direction::Right)
//{
//	cout << 0;
//}
//
//P1.Ships[0].IsHit({ 0,3 });
//cout << "Status: " << P1.Ships[0].Status.at(0) << P1.Ships[0].Status.at(1) << P1.Ships[0].Status.at(2) << P1.Ships[0].Status.at(3) << P1.Ships[0].Status.at(4) << "\n";
//cout << P1.Ships[0].Sunk;
