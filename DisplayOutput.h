
#pragma once

#include "stdafx.h"
#include <string>
#include "Global_Definitions.h"
#include "Player.h"
#include "Global_Definitions_DisplayOutput.h"
using namespace std;

// Anmerkung zr Funktion Beschleunigung(...) konnte leider nicht testen, da Dateien nicht vorhanden
// möglicherweise wird der schneller - Button nur so lange ausgegeben wie er noch nicht betätigt wurde 
// wenn er getätigt wurde und danach die Funktion nicht mehr aufgerufen wird, wird auch der Button nicht mehr gezeichnet und auch nicht mehr abgefragt
class DisplayOutput
{
public:
	// Funktion, um die Spielfelder, die Schiffe und die Treffer der Spieler darzustellen
	// 
	// Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	// int Farbe : Farbe der Schiffe des Spielers
	void Ausgabe(Player Spieler1, Player Spieler2, int FarbeSpieler1, int FarbeSpieler2);

	// einmaliger Aufruf zum Positionieren eines Grafikfensters
	//
	// Position Bildschirm: Position des Grafikfensters auf dem Bildschrim
	// int Startpunkt : "Ankerpunkt" auf der Grafikoberfläche (wird zur Skalierung der Breite benötigt)
	void Grafikfenster(Position Bildschirm, int Startpunkt);

	// Abfrage, ob Spiel schneller laufen soll (schneller  => true, nicht schneller/ unverändert => false)
	// Ausgabe eines Buttons "schneller"
	// 
	// int Startpunkt : "Ankerpunkt" auf der Grafikoberfläche zur Positionierung des "schneller"-Buttons
	bool Beschleunigung(int Startpunkt);

	//Breite eines Kaestchens des dargestellten Spielfeldes
	int Kaestchengroesse;  // sinnvolle Angabe: 20


private:
	// diese Funktionen werden in der Funktion Ausgabe(...) aufgerufen

	//	Funktion zum Erstellen eines Spielfeldes linke obere Ecke zur Orientierung zurück
	//	
	//	Position Bildschirm : Koordinate der linken oberen Ecke des Grafikfensters
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//	int Startpunkt : "Ankerpunkt" auf der Grafikoberfläche
	Position SpielfeldErstellen(Position Bildschirm, int index, int Startpunkt);

	//  Ausgabe einer Legende mit den wichtigen Informationen zum Spieler ( Verteidigungsstartegie, Angriffsstrategie, Schüsse, versenkte Schiffe etc.)
	//	
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  int index : Nummer des Spielers, Spieler 1 = 1 und Spieler2 = 2
	//  Player Spieler: Objekt der Klasse Player, beinhaltet Informationen zu den Schiffen etc. des Spielers
	Position DisplayOutput::Legende(Position EckpunktSpielfeld, int Startpunkt, int index, Player Spieler);

	//  Funktion zeichnet ein Schiff in das Spielfeld (muss überarbeitet werden / im Bezug auf Klasse ship)
	//	
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//	Ship Schiff : darzustellendes Schiff
	//	int Farbe : Farbe der Schiffe des Spielers
	void DarstellungSchiff(Position EckpunktSpielfeld, Ship Schiff, int Farbe);

	//  kennzeichnet ein getroffenes Feld
	//	
	//	Position EckpunktSpielfeld : linke obere Ecke des Spielfeldes
	//  Position Treffer : Koordinaten des Treffers 
	//  int Farbe : Farbe des Treffers (Rot / Weiss)
	void getroffenesFeld (Position EckpunktSpielfeld, Position Treffer, int Farbe);

};

