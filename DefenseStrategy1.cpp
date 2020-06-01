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



void DefenseStrategy1(int *ShipNumber, DefendAction *Action, MoveDirection *MoveDir, TurnDirection *TurnDir)
{
	// DefendAction (Nothing, Move, Turn) zufällig wählen
	int rndAction = (rand() % 3);	// ohne Turn: (rand() % 2); // mit Turn: (rand() % 3);
	int rndMoveDir = 0;
	int rndTurnDir = 0;

	// zufällige Wahl was getan werden soll
	switch (rndAction)
	{
	case 0:									// nichts tun
		*Action = DefendAction::Nothing;
		break;

	case 1:									// Move
		*Action = DefendAction::Move;		// DefAction = Move
		*ShipNumber = (rand() % 10);		// zufällige ShipNumber
		rndMoveDir = (rand() % 2);			// Richtungswahl zufällig
		switch (rndMoveDir)
		{
			case 0:
				*MoveDir = MoveDirection::Forward;
				break;
			case 1:
				*MoveDir = MoveDirection::Backward;
				break;
		}

		break;

	case 2:
		*Action = DefendAction::Turn;	// DefAction soll Turn sein
		*ShipNumber = (rand() % 10);	// zufällige ShipNumber
		rndTurnDir = (rand() % 2);
		switch (rndTurnDir)
		{
			case 0:
				*TurnDir = TurnDirection::LeftTurn;
				break;
			case 1:
				*TurnDir = TurnDirection::RightTurn;
				break;
		}
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