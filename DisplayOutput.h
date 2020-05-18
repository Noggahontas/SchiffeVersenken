
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h";
#include "Player.h"

using namespace std;



class DisplayOutput
{
public:
	// Funktion, um die Schiffe des Spielers und Treffer auf dem Spielfeld darzustellen
	// Parameter:
	// int Kaestchengroesse: Breite eines Kaestchens des dargestellten Spielfeldes
	// Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	// int Farbe : Farbe der Schiffe des Spielers
	void Ausgabe(int Kaestchengroesse, Player Spieler, int Farbe);

private:
	// diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	//	Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zurück
	//	Parameter: 
	//	Position Bildschirm : Koordinate der linken oberen Ecke des Grafikfensters
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	Position SpielfeldErstellen(Position Bildschirm, int Kaestchengroesse);

	//  Ausgabe einer Legende [unnoetig, nur zu Kontrollzwecken]
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//	int FarbeSpieler1, int FarbeSpieler2 : Farbe der Schiffe der Spieler
	void Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int FarbeSpieler1, int FarbeSpieler2);

	//  Funktion zeichnet ein Schiff in das Spielfeld (muss überarbeitet werden / im Bezug auf Klasse ship)
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	Position Schiffsposition: Koordinaten der linken oberen Ecke des darzustellenden Schiffs
	//	int Farbe : Farbe der Schiffe des Spielers
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//	int Schiffslaenge : Länge des Schiffes 
	//	Direction AusrichtungSchiff: Ausrichtung des darzustellenden Schiffs auf dem Spielfeld

	void DarstellungSchiff(Position EckpunktSpielfeld, Position Schiffsposition, int Kaestchengroesse, int Farbe,  int Schiffslaenge, Direction AusrichtungSchiff);

	// kennzeichnet ein getroffenes Feld
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers 
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Kaestchengroesse);

};

