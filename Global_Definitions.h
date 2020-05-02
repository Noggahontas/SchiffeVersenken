#pragma once

struct Position { int x; int y; };	//Position im Spielfeld mit x- und y-Koordinate

enum Direction { Right, Down };	// Richtung in die das Schiff von der Startposition aus ausgerichtet ist

enum TurnDirection{ Left, Right };	// Richtung, in die ein Schiff gedrecht werden kann