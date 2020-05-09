#pragma once

struct Position { int x; int y; };	//Position im Spielfeld mit x- und y-Koordinate

enum AttackDirection { N, E, S, W };	// In Angriffsstrategie3 für den Richtungswechsel

enum Direction { Right, Down };	// Richtung in die das Schiff von der Startposition aus ausgerichtet ist

enum TurnDirection{ LeftTurn, RightTurn };	// Richtung, in die ein Schiff gedrecht werden kann

enum MoveDirection{ LeftMove, RightMove, UpMove, DownMove};	// Richtung, ind ie ein Schiff bewegt werden kann