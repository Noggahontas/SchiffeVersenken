#pragma once
#include "Ship.h"
#include "Global_Definitions.h"
#include <vector>
using namespace std;


class Player
{
public:
	Ship Ships[10];							// Array vom Typ/Klasse Ships; alle 10 Schiffe, die ein Spieler besitzt
	vector<Position> Last3ShotsOfOpponent;	// Hier werden die letzten 3 Schüsse des Gegners gespeichert. [0]=aktuellster Schuss, [2]= Schuss vor 2 Runden.  Am Anfang alle Elemente = NULL
	int AttackStrategy;						// Hier wird ein Schlüssel entsprechend der gewählten Angriffsstrategie gespeichert
	int DefenseStrategy;					// Hier wird ein Schlüssel entsprechend der gewählten Verteidigungsstrategie gespeichert
	bool Lost;								// Gibt an ob Spieler verloren hat. Verloren wenn alle seine Schiffe versenkt wurden. 1 = Verloren, 0 = nich nicht verloren

	int MissedShotsOfOpponent;				// Hier wird während eines Spiels mitgezählt wie viele Schüsse der Gegner schon ins Leere geschossen hat
	int HitShotsOfOpponent;					// Hier wird während eines Spiels mitgezählt wie viele Schüsse der Gegner schon getroffen hat
	int SunkShipsByOpponent;				// Hier wird gezählt wie viele Schiffe der Gegner bei diesem Spielr versenkt hat



public:
	AttackResult ShotOn(Position Shot);		// Schuss von Gegner auf Koordinaten Shot	
											// ändert Last3ShotsOfOpponent
											// Rückgabe als Strukt 
											// Gibt zurück ob ein Schiff getroffen wurde: Hit=1= getroffen, Hit=0=nicht getroffen
											// Gibt zurück ob ein Schiff versenkt wurde: Sunk=1=versenkt, Sunk=0=nicht versenkt

	bool Turn(int ShipNumber); // Übergabe welches Schiff gedreht werden soll. Nummer Schiff = Index i aus Array Ships[i] 
														// Übergabe Richtung, in die gedrecht werden soll. Left=1 oder Right=2
														// Kollisionsabfrage ob Drehen möglich, wenn ja:
														// Ändert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
														// Rückgabe ob Drehen möglich/erfolgreich war. Geklappt=1, Nicht geklappt=0

	bool Move(int ShipNumber, MoveDirection Direction);	// Übergabe welches Schiff bewegt werden soll. Nummer Schiff = Index i aus Array Ships[i] 
														// Übergabe Richtung, in die bewegt werden soll. LeftMove, RightMove, UpMove, DownMove
														// Kollisionsabfrage ob Drehen möglich, wenn ja:
														// Ändert Startposition (StartPos) und Ausrichtung (Direction) von Schiff
														// Rückgabe ob Bewegen möglich/erfolgreich war. Geklappt=1, Nicht geklappt=0	

	void CheckIfLost();									// Prüft ob alle Schiffe eines Spielers versenkt wurden und aktualisiert ggf. Variable Lost		



	Position FindAttackShot(AttackResult LastAttackResult);// Gibt je nach gewählter Angriffsstrategie (AttackStrategy) eines Spielers Koordinaten zurück,
														// auf die geschossen werden soll
														// Übergabe von Ergebnis dees letzten eigenen Schusses (Treffer, Versenkt)

	void DefensiveAction(bool WasLastShotAHit);			// Ermittelt je nach gewählter Angriffsstrategie einen Verteidigungsmove: 
														// Bewegen oder Drehen und welches Schiff, oder auch gar nichts
														// Ruft ggf. Funktion Turn oder Move auf 

	Player();		// Konstruktor 
					// Stößt Kontruktor für jedes Schiff an
					//legt Größe von Last3ShotsOfOpponent fest und initialisiert mit NULL
					// Wählt zufällig AttackStrategy und DefenseStrategy aus

	
														
};




// Testen Funktion DefensiveAction

//Player P1;
//
//P1.DefenseStrategy = 2;
//
//cout << P1.Ships[1].StartPos.x << P1.Ships[1].StartPos.y << "\n";
//
//bool Hit = 0;
//
//P1.DefensiveAction(Hit);
//
//cout << P1.Ships[1].StartPos.x << P1.Ships[1].StartPos.y << "\n";
//


//_________________________________________________________________________

//Testen Funktion CheckIfLost

//
//Player P1;
//cout << P1.Lost << "\n";
//
//P1.Ships[0].Sunk = 1;
//P1.CheckIfLost();
//cout << P1.Lost << "\n";
//
//for (int i = 0; i < 10; i++)
//{
//	P1.Ships[i].Sunk = 1;
//}
//P1.CheckIfLost();
//cout << P1.Lost << "\n";




//_________________________________________________________________________

// Testen Funktion Move

//Player P1;
//
//int i = 6; // Number of Ship to be moved

//P1.Ships[i].Status.at(0) = 1;	// Schiff wurde schon getroffen -> bewegungsunfähig

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





// Lösung Problem enum -> Typumwandlung
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
//AttackResult Result;
//
//Result = P1.ShotOn({ 0,7 });
//cout << "\n" << Result.Hit << "," << Result.Sunk << "\n";
//cout << "Status getr. Schiff: " << P1.Ships[3].Status.at(0) << P1.Ships[3].Status.at(1) << P1.Ships[3].Status.at(2);
//cout << "\n letzte 3 Schüsse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//Result = P1.ShotOn({ 1,7 });
//cout << "\n" << Result.Hit << "," << Result.Sunk << "\n";
//cout << "Status getr. Schiff: " << P1.Ships[3].Status.at(0) << P1.Ships[3].Status.at(1) << P1.Ships[3].Status.at(2);
//cout << "\n letzte 3 Schüsse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//Result = P1.ShotOn({ 2,7 });
//cout << "\n" << Result.Hit << "," << Result.Sunk << "\n";
//cout << "Status getr. Schiff: " << P1.Ships[3].Status.at(0) << P1.Ships[3].Status.at(1) << P1.Ships[3].Status.at(2);
//cout << "\n" << "Schiff-Variable Sunk:" << P1.Ships[3].Sunk;
//cout << "\n letzte 3 Schüsse: ";
//for (int i = 0; i < 3; i++)
//{
//	cout << "{" << P1.Last3ShotsOfOpponent.at(i).x << P1.Last3ShotsOfOpponent.at(i).y << "} ";
//}
//
//Result = P1.ShotOn({ 2,7 });
//cout << "\n" << Result.Hit << "," << Result.Sunk << "\n";
//cout << "Status getr. Schiff: " << P1.Ships[3].Status.at(0) << P1.Ships[3].Status.at(1) << P1.Ships[3].Status.at(2);
//cout << "\n" << "Schiff-Variable Sunk:" << P1.Ships[3].Sunk;
//cout << "\n letzte 3 Schüsse: ";
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
