#pragma once

struct Position { int x; int y; };	// Position im Spielfeld mit x- und y-Koordinate

 

enum class Direction { Right  , Down };	// Richtung in die das Schiff von der Startposition aus ausgerichtet ist (Orientation)

enum class TurnDirection{ LeftTurn, RightTurn };	// Richtung, in die ein Schiff gedrecht werden kann

enum class MoveDirection{ Forward, Backward};	// Richtung, in die ein Schiff bewegt werden kann




// Farben in der RGB - Darstellung
#define SCHWARZ 0
#define WEISS RGB(255,255,255)
#define BLAU RGB(0,0,255)
#define GRUEN RGB(0,255,0)
#define ROT RGB(255,0,0)
#define GRAU RGB(192,192,192)

enum class DefendAction { Nothing, Move, Turn };	// Aktion, die f�r ein Schiff beim verteidigen ausgef�hrt werden soll: Bewegen oder Drehen

struct AttackResult { bool Sunk; bool Hit; };		// Resultate bei einem Schuss. 
													// Hit: Wurde ein Schiff getroofen;   Sunk: Wurde ein Schiff versenkt
											