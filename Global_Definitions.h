#pragma once

struct Position { int x; int y; };	//Position im Spielfeld mit x- und y-Koordinate

enum Direction { Right, Down };	// Richtung in die das Schiff von der Startposition aus ausgerichtet ist

enum TurnDirection{ LeftTurn, RightTurn };	// Richtung, in die ein Schiff gedrecht werden kann

enum MoveDirection{ LeftMove, RightMove, UpMove, DownMove};	// Richtung, ind ie ein Schiff bewegt werden kann

struct Schiffsposition { Position linkeEckeOben; char ausrichtung; }; // Schiff muss zum Lokalisieren linke obere Ecke und Ausrichtung besitzen