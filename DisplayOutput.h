
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h";
#include "Player.h"

using namespace std;



class DisplayOutput
{
public:


	void Ausgabe(int Kaestchengroesse, Player Spieler, int Farbe);

private:

	//Initialisierung
	// int Initialisierung();

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
	//	Schiffsposition LokalisierungSchiff : beinhaltet Position (Koordinaten) des Schiffes und die Ausrichtung // muss noch angepasst werden
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//	int Schiffslaenge : Länge des Schiffes [zu Testzwecken. später Zugriff über player/ship ...]
	//	string Spieler : Kennung Spieler [zu Testzwecken ]
	void DarstellungSchiff(Position EckpunktSpielfeld, int Kaestchengroesse, int Farbe, Position Schiffsposition, int Schiffslaenge, Direction AusrichtungSchiff);

	// kennzeichnet ein getroffenes Feld
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Kaestchengroesse);

};

