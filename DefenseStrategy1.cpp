#include "stdafx.h"
#include <iostream>
#include "Global_Definitions_Strategies.h"
#include "Global_Definitions.h"
#include "DefenseStrategy1.h"
#include <time.h>
#include <vector>

using namespace std;

/*
------------------------------------------------------------------------------------------------------------------------------
Verteidigungsstrategie soll nach dem Schuss des Gegners eines der eigenen Schiffe (Zufall)
drehen, bewegen oder nichts tun (was davon und Richtung: Zufall).

------------------------------------------------------------------------------------------------------------------------------
*/



void DefenseStrategy1(int *ShipNumber, DefendAction *Action, MoveDirection *MoveDir)
{
	int rndAction = (rand() % 3);							// DefendAction (Nothing, Move, Turn) soll zufällig gewählt werden
	int rndMoveDir = 0;										// Zufällige Bewegungsrichtung wählen
		
	switch (rndAction)
	{
	case 0:													// Erster Fall: nichts tun
		*Action = DefendAction::Nothing;					// DefendAction auf Nothing setzen
		break;

	case 1:													// Zweiter Fall: ein Schiff soll sich bewegen
		*Action = DefendAction::Move;						// DefendAction auf Move setzen
		*ShipNumber = (rand() % 10);						// zufälliges Schiff auswählen
		rndMoveDir = (rand() % 2);							// zufällige Richtungswahl
		switch (rndMoveDir)
		{
			case 0:											// Erster Fall: Vorwärts bewegen
				*MoveDir = MoveDirection::Forward;			
				break;
			case 1:											// Zweiter Fall: Rückwärts bewegen
				*MoveDir = MoveDirection::Backward;
				break;
		}
		break;

	case 2:													// Dritter Fall: ein Schiff soll sich drehen
		*Action = DefendAction::Turn;						// DefendAction auf Turn setzen
		*ShipNumber = (rand() % 10);						// zufälliges Schiff auswählen
		break;
	}
	return;
}

/*

// Test DefStrat1:
int ShipNumber;
DefendAction Action = DefendAction::Nothing;
MoveDirection MoveDir = MoveDirection::Forward;
TurnDirection TurnDir = TurnDirection::LeftTurn;



DefenseStrategy1(&ShipNumber, &Action, &MoveDir, &TurnDir);

*/