
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h";
#include "Player.h"

using namespace std;

/*
	fuer die main/ zum Testen:

	Player Spieler1, Spieler 2;
	DisplayOutput Bildschirm;
	Bildschirm.Ausgabe(20, Spieler1, Spieler2, BLAU, GRUEN);

	Initialisierung eines Objektes Bildschirm der Klasse DisplayOutput und Spieler1, Spieler2 der Klasse Player
*/


class DisplayOutput
{
public:
	// Funktion, um die Schiffe des Spielers und Treffer auf dem Spielfeld darzustellen
	// Parameter:
	// int Kaestchengroesse: Breite eines Kaestchens des dargestellten Spielfeldes // sinnvolle Angabe: 20
	// Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	// int Farbe : Farbe der Schiffe des Spielers
	// int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	void Ausgabe(int Kaestchengroesse, Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

private:
	// diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	//	Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zurück
	//	Parameter: 
	//	Position Bildschirm : Koordinate der linken oberen Ecke des Grafikfensters
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	Position SpielfeldErstellen(Position Bildschirm, int Kaestchengroesse, int index);

	//  Ausgabe einer Legende [unnoetig, nur zu Kontrollzwecken]
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	//	int FarbeSpieler1, int FarbeSpieler2 : Farbe der Schiffe der Spieler
	void Legende(Position EckpunktSpielfeld, int Kaestchengroesse, int FarbeSpieler1, int FarbeSpieler2);

	//  Funktion zeichnet ein Schiff in das Spielfeld (muss überarbeitet werden / im Bezug auf Klasse ship)
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	Ship Schiff : darzustellendes Schiff
	//	int Farbe : Farbe der Schiffe des Spielers
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes

	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Kaestchengroesse, int Farbe);

	// kennzeichnet ein getroffenes Feld
	//	Parameter:
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers 
	//	int Kaestchengroesse : Breite eines Kaestchens des dargestellten Spielfeldes
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Kaestchengroesse, int Farbe);

};

