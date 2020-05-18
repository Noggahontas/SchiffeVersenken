#pragma once

struct Position { int x; int y; };	// Position im Spielfeld mit x- und y-Koordinate

enum AttackDirection { N, E, S, W };	// Für den Richtungswechsel in AttackStrategy3 (Sprialform)

enum class Direction { Right  , Down };	// Richtung in die das Schiff von der Startposition aus ausgerichtet ist (Orientation)

enum class TurnDirection{ LeftTurn, RightTurn };	// Richtung, in die ein Schiff gedrecht werden kann

enum class MoveDirection{ Forward, Backward};	// Richtung, ind ie ein Schiff bewegt werden kann

//struct Schiffsposition { Position linkeEckeOben; char ausrichtung; }; // Schiff muss zum Lokalisieren linke obere Ecke und Ausrichtung besitzen


// Farben in der RGB - Darstellung
#define SCHWARZ 0
#define WEISS RGB(255,255,255)
#define BLAU RGB(0,0,255)
#define GRUEN RGB(0,255,0)
#define ROT RGB(255,0,0)

