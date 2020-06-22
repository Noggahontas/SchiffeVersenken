#pragma once
#include "Ship.h"
#include "Global_Definitions.h"
#include <vector>
using namespace std;
#include <string>
#include "Global_Definitions_Strategies.h"


class Player
{
public:
	Ship Ships[10];							// Array vom Typ/Klasse Ships; alle 10 Schiffe, die ein Spieler besitzt
	vector<Position> Last3ShotsOfOpponent;	// Hier werden die letzten 3 Schüsse des Gegners gespeichert. [0]=aktuellster Schuss, [2]= Schuss vor 2 Runden.  Am Anfang alle Elemente = -1
	int AttackStrategy;						// Hier wird ein Schlüssel entsprechend der gewählten Angriffsstrategie gespeichert
	int DefenseStrategy;					// Hier wird ein Schlüssel entsprechend der gewählten Verteidigungsstrategie gespeichert
	bool Lost;								// Gibt an ob Spieler verloren hat. Verloren wenn alle seine Schiffe versenkt wurden. 1 = Verloren, 0 = nich nicht verloren

	int MissedShotsOfOpponent;				// Hier wird während eines Spiels mitgezählt wie viele Schüsse der Gegner schon ins Leere geschossen hat
	int HitShotsOfOpponent;					// Hier wird während eines Spiels mitgezählt wie viele Schüsse der Gegner schon getroffen hat
	int SunkShipsByOpponent;				// Hier wird gezählt wie viele Schiffe (von diesem Spieler) der Gegner in diesem Spiel versenkt hat

	bool ReadInError;						// Angabe ob es beim Einlesen der Textdateien zum Schiffe setzen einen Fehler gab

	// Für die Angriffsstrategien
	Position SaveCoordinates;
	int AttStrategy2Rounds;
	bool AttStrategy3DirectionSet;
	AttackDirection AttStrategy3_4Direction;
	bool AttStartegy4AlreadyShot;
	bool AttStrategy4DirectionChoice;
	bool AttStarategy4FieldBorder;
	Position AttStrategy4FirstHit;


public:
/*
	Funktion: Schuss von Gegner auf Koordinaten Shot ausführen
	Input:	- ShotOn: Koordinaten, auf die der Gegner schießt
	Transienten: Last3ShotsOfOpponent, HitShotsOfOpponent, MissedShotsOfOpponent, SunkShipsByOpponent
	Output: Als Struct AttackResult Information ob ein Schiff getroffen wurde und ob ein Schiff versenkt wurde
*/
	AttackResult ShotOn(Position Shot);		


	/*
		Funktion: Dreht ein Schiff wenn möglich (Kollisionsabfrage)
		Input:	- ShipNumber: welches Schiff gedreht werden soll. Index i aus Array Ships[i] 
		Transienten: Ship[ShipNumber].StartPos, Ship[ShipNumber].Direction
		Output: Angabe ob Drehen möglich/ erfolgreich war
	*/
	bool Turn(int ShipNumber);							



	/*
		Funktion: Bewegt ein Schiff  wenn möglich (Kollisionsabfrage)
		Input:	- ShipNumber: welches Schiff bewegt werden soll. Index i aus Array Ships[i]
		Transienten: Ship[ShipNumber].StartPos, Ship[ShipNumber].Direction
		Output: Angabe ob Bewegen möglich/ erfolgreich war
	*/
	bool Move(int ShipNumber, MoveDirection Direction);	



	/*
		Funktion: Prüft ob alle Schiffe eines Spielers versenkt wurden und aktualisiert ggf. Variable Lost	
		Input:Ships[10]
		Transienten: Lost	
	*/
	void CheckIfLost();									


	/*
		Funktion: Gibt je nach gewählter Angriffsstrategie (AttackStrategy) eines Spielers Koordinaten zurück, auf die geschossen werden soll
		Input:	LastAttackResult: Ergebnis des letzten eigenen Schusses (Treffer, Versenkt)
		Output: Koordinaten, auf die geschossen werden soll
	*/
	Position FindAttackShot(AttackResult LastAttackResult);	


	/*
		Funktion:	- Ermittelt je nach gewählter Verteidigungsstrategie einen Verteidigungsmove: Bewegen oder Drehen und welches Schiff, oder auch gar nichts
					- Ruft ggf. Funktion Turn oder Move auf 
	*/
	void DefensiveAction();									


	/*
		Funktion: Konstruktor mit Parameter
		Input:	ModeSetShips: Modus für Auswählen der Text-Dateien zum Schiffe setzen
		Transienten: Alle Klassenvariablen initialisieren
	*/
	Player(int ModeSetShips);		


	
	void lex(string FileName);		// Ruft lexikalische Analyse auf



	/*
		Funktion:		Generieren neuer Angriffskoordinaten (Zufall)
		Input:			-
		Transienten:	new_Position
		Output:			new_Position: die neuen anzugreifenden Koordinaten
	*/
	Position AttackStrategy1();



	/*
		Funktion:		Generieren neuer Angriffskoordinaten (diagonale Linien)
		Input:			-
		Transienten:	Strategy_Rounds: Zähler für Durchläufe
						SaveCoordinates: die letzten Koordinaten
		Output:			Pos: neue Angriffskoordinaten
	*/
	Position AttackStrategy2();



	/*
		Funktion:		Generieren neuer Angriffskoordinaten (Spirale)
		Input:			-

		Transienten:	AttStrategy3_4Directions: Richtung des Angriffs
		Output:			Pos: neue Angriffskoordinaten
	*/
	Position AttackStrategy3();



	/*
		Funktion:			Generieren neuer Angriffskoordinaten
		Input:				LastShotHit: Information, ob der letzte eigene Schuss ein Treffer war
							sunk: Information, ob das Schiff, das mit dem letzten Angriff angegriffen wurde, gesunken ist
		Transienten:		SaveCoordinates: die letzten Koordinaten
							alreadyShot/AttStrategy4AlreadyShot: Information, ob schon geschossen wurde
							Direction/AttStrategy3_4Direction: Richtung des Angriffs
							DirectionChoice/AttStrategy4DirectionChoice: Information, ob eine Richtung gewählt wurde
							FieldBorder/AttStrategy4FieldBorder: Information zur Spielfeldrandkollision
							first_hit/AttStrategy4FirstHit: Zufallskoordinaten, falls der erste Schuss ein Treffer war
		Output:				Pos: neue Angriffskoordinaten
	*/
	Position AttackStrategy4(bool* LastShotHit, bool* sunk);




	/*
		Funktion:			Wählen der Art der Verteidigungsaktion
		Input:				ShipNumber: Nummer des Schiffs
							Action: Art der Aktion, die durchgeführt werden soll (nichts, bewegen, drehen)
							MoveDir: Bewegungsrichtung
		Transienten:		ShipNumber (Teil der Funktion DefensiveAction)
							Action (Teil der Funktion DefensiveAction)
							MoveDir (Teil der Funktion DefensiveAction)
		Output:				-
	*/
	void DefenseStrategy1(int* ShipNumber, DefendAction* Action, MoveDirection* MoveDir);
														
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
